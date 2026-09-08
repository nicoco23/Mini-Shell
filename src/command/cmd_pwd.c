/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:50:36 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/08 13:50:37 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, PATH_MAX))
		return (putendl_check(cwd, 1));
	pwd = env_get(shell->env, "PWD");
	if (pwd)
		return (putendl_check(pwd, 1));
	return (write_error("pwd"), 1);
}
