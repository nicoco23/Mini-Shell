/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:52:26 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/08 16:14:01 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_free(t_shell *shell)
{
	rl_clear_history();
	close_if_open(shell->saved_in);
	close_if_open(shell->saved_out);
	shell->saved_in = -1;
	shell->saved_out = -1;
	free_cmds(shell->cmds);
	shell->cmds = NULL;
	env_clear(&shell->env);
	free(shell->line);
	shell->line = NULL;
	free(shell->pids);
	shell->pids = NULL;
}

void	clean_exit(t_shell *shell, int code)
{
	shell_free(shell);
	close_if_open(STDIN_FILENO);
	close_if_open(STDOUT_FILENO);
	exit(code);
}
