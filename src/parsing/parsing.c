/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:54:34 by ltournie          #+#    #+#             */
/*   Updated: 2026/08/25 16:56:04 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_blank(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (!*line);
}

static int	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;

	if (!*line || is_blank(line))
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

	line = readline("\033[1;35mMouliSwag\033[0m 🦁​");
	if (!line)
	{
		ft_printf("exit\n");
		exit(shell->last_exit);
	}
	process_line(line, shell);
	free(line);
	return (0);
}
