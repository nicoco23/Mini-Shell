/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 08:50:43 by codespace         #+#    #+#             */
/*   Updated: 2026/09/07 21:29:26 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	if (env_from_envp(envp, &shell.env))
		return (ft_putstr_fd(
				"mouliswag: fatal: environment allocation failed\n", 2), 1);
	shell.cmds = NULL;
	shell.line = NULL;
	shell.pids = NULL;
	shell.last_exit = 0;
	init_shell_env(&shell);
	while (1)
		parsing(&shell);
	return (0);
}
