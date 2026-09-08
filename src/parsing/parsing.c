/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:54:34 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/08 12:12:34 by ntassin          ###   ########.fr       */
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
	shell->cmds = build_cmds(token);
	free_tokens(token);
	if (!shell->cmds)
		return (0);
	if (read_heredocs(shell))
	{
		shell->last_exit = 130;
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
	if (!tokens)
		return (shell->last_exit = err * EXIT_SYNTAX_ERROR, 0);
	if (!check_syntax(tokens))
	{
		shell->last_exit = EXIT_SYNTAX_ERROR;
		return (free_tokens(tokens), 0);
	}
	return (build_and_run(shell, tokens));
}

static char	*read_prompt_line(void)
{
	char	*line;
	int		len;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
	{
		rl_outstream = stderr;
		return (readline(PROMPT));
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
	shell->line = read_prompt_line();
	if (!shell->line)
	{
		ft_printf("exit\n");
		clean_exit(shell, shell->last_exit);
	}
	if (g_signal == SIGINT)
	{
		shell->last_exit = 130;
		g_signal = 0;
	}
	process_line(shell->line, shell);
	free(shell->line);
	shell->line = NULL;
	return (0);
}

