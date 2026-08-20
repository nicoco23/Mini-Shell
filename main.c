/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 08:50:43 by codespace         #+#    #+#             */
/*   Updated: 2026/08/20 15:45:50 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env(char **env, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(env[i++]);
	free(env);
}

static char	**copy_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (free_env(env, i), NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = copy_env(envp);
	if (!shell.env)
		return (ft_putstr_fd(
				"mouliswag: fatal: environment allocation failed\n", 2), 1);
	debug_print_env(shell.env);
	shell.cmds = NULL;
	shell.last_exit = 0;
	while (1)
		parsing(&shell);
	return (0);
}
