/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:54:34 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/09 23:54:27 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_blank(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (!*line);
}

static int	build_and_run(t_shell *shell, t_token *token)
{
	int	hd;

	shell->cmds = build_cmds(token);
	free_tokens(token);
	if (!shell->cmds)
		return (0);
	hd = read_heredocs(shell->cmds, shell);
	if (hd != 0)
	{
		if (hd == -1)
			shell->last_exit = 130;
		else
			shell->last_exit = 1;
		free_cmds(shell->cmds);
		return (shell->cmds = NULL, 0);
	}
	exec(shell);
	free_cmds(shell->cmds);
	return (shell->cmds = NULL, 1);
}

static int	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	int		err;

	if (!line || is_blank(line))
		return (0);
	add_history(line);
	tokens = lexer(line, shell, &err);
	if (err)
		return (shell->last_exit = EXIT_SYNTAX_ERROR, 0);
	if (!tokens)
		return (shell->last_exit = 0, 0);
	if (!check_syntax(tokens))
	{
		shell->last_exit = EXIT_SYNTAX_ERROR;
		return (free_tokens(tokens), 0);
	}
	return (build_and_run(shell, tokens));
}

char	*read_input_line(const char *prompt)
{
	char	*line;
	size_t	len;

	if (isatty(STDIN_FILENO))
	{
		rl_outstream = stderr;
		return (readline(prompt));
	}
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

int	parsing(t_shell *shell)
{
	setup_signal_prompt();
	if (g_signal == SIGINT)
	{
		if (isatty(STDIN_FILENO))
			write(2, "\n", 1);
		g_signal = 0;
	}
	shell->line = read_input_line("MouliSwag $ ");
	if (g_signal == SIGINT)
	{
		shell->last_exit = 130;
		g_signal = 0;
	}
	if (!shell->line)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", 2);
		clean_exit(shell, shell->last_exit);
	}
	process_line(shell->line, shell);
	free(shell->line);
	shell->line = NULL;
	return (0);
}
