/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:54:34 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/08 15:38:07 by ltournie         ###   ########.fr       */
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
	if (read_heredocs(shell->cmds))
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

	if (!line || is_blank(line))
		return (0);
	add_history(line);
	tokens = lexer(line, shell);
	if (!tokens)
		return (shell->last_exit = EXIT_SYNTAX_ERROR, 0);
	if (!check_syntax(tokens))
	{
		shell->last_exit = EXIT_SYNTAX_ERROR;
		return (free_tokens(tokens), 0);
	}
	return (build_and_run(shell, tokens));
}

static char	*read_prompt_line(t_shell *shell)
{
	char	*line;
	int		len;

	if (isatty(STDIN_FILENO))
	{
		if (shell->last_exit != 130)
			return (readline("\1\033[1;35m\2MouliSwag\1\033[0m 🦁​\2"));
		else
		{
			if (g_signal == SIGINT)
			{
				write(1, "\n", 1);
				g_signal = 0;
			}
			return (readline("\1\033[1;35m\2MouliSwag\1\033[0m 🦁​\2"));
		}
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
	shell->line = read_prompt_line(shell);
	if (g_signal == SIGINT)
	{
		shell->last_exit = 130;
		g_signal = 0;
	}
	if (!shell->line)
	{
		ft_printf("exit\n");
		clean_exit(shell, shell->last_exit);
	}
	process_line(shell->line, shell);
	free(shell->line);
	shell->line = NULL;
	return (0);
}
