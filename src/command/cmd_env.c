/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:50:30 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/08 13:50:31 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_env(t_env *env)
{
	while (env)
	{
		if (env->visibility && env->value)
		{
			if (put_check(env->name, 1) || put_check("=", 1)
				|| putendl_check(env->value, 1))
				return (write_error("env"), 1);
		}
		env = env->next;
	}
	return (0);
}
