/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 08:50:43 by codespace         #+#    #+#             */
/*   Updated: 2026/09/08 21:18:33 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("Too many arguments.\n", 2);
		return (1);
	}
	if (env_from_envp(envp, &shell.env))
		return (ft_putstr_fd(
				"mouliswag: fatal: environment allocation failed\n", 2), 1);
	shell.cmds = NULL;
	shell.line = NULL;
	shell.pids = NULL;
	shell.saved_in = -1;
	shell.saved_out = -1;
	shell.last_exit = 0;
	init_shell_env(&shell);
	while (1)
		parsing(&shell);
	return (0);
}
