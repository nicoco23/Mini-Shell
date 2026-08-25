/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 20:09:19 by ntassin           #+#    #+#             */
/*   Updated: 2026/08/25 20:40:28 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint_wait(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	setup_signal_wait(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint_wait;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
