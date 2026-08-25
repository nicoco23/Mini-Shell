/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:54:34 by ltournie          #+#    #+#             */
/*   Updated: 2026/08/25 18:10:10 by ntassin          ###   ########.fr       */
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
	debug_print_cmds(shell->cmds);
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
	shell->cmds = build_cmds(tokens);
	free_tokens(tokens);
	if (!shell->cmds)
		return (0);
	// debug_print_cmds(shell->cmds);
	exec(shell);
	free_cmds(shell->cmds);
	return (shell->cmds = NULL, 1);
}

int	parsing(t_shell *shell)
{
	char	*line;

	setup_signal_prompt();
	line = readline("\033[1;35mMouliSwag\033[0m 🦁​");
	if (!line)
	{
		ft_printf("exit\n");
		exit(shell->last_exit);
	}
	if (g_signal == SIGINT)
	{
		shell->last_exit = 130;
		g_signal = 0;
	}
	process_line(line, shell);
	free(line);
	return (0);
}
