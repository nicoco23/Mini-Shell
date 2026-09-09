/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:52:20 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/09 22:06:13 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	return (ft_strncmp(name, "cd", 3) == 0
		|| ft_strncmp(name, "pwd", 4) == 0
		|| ft_strncmp(name, "echo", 5) == 0
		|| ft_strncmp(name, "env", 4) == 0
		|| ft_strncmp(name, "export", 7) == 0
		|| ft_strncmp(name, "unset", 6) == 0
		|| ft_strncmp(name, "exit", 5) == 0);
}

static int	dispatch_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*name;

	name = cmd->args[0];
	if (ft_strncmp(name, "cd", 3) == 0)
		return (cmd_cd(shell, cmd));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (cmd_pwd(shell));
	if (ft_strncmp(name, "echo", 5) == 0)
		return (cmd_echo(cmd->args));
	if (ft_strncmp(name, "env", 4) == 0)
		return (cmd_env(shell->env));
	if (ft_strncmp(name, "exit", 5) == 0)
		return (cmd_exit(shell, cmd->args));
	if (ft_strncmp(name, "export", 7) == 0)
		return (cmd_export(shell, cmd->args));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (cmd_unset(cmd->args, shell));
	return (0);
}

int	run_builtin(t_shell *shell, t_cmd *cmd)
{
	if (apply_redirs(cmd))
		return (1);
	if (!cmd->args || !cmd->args[0])
		return (0);
	return (dispatch_builtin(shell, cmd));
}
