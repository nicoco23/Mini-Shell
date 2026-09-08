/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:50:37 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/08 13:50:38 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_unset(char **args, t_shell *shell)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (args[++i])
	{
		if (!is_valid_id(args[i]))
		{
			ft_putstr_fd("mouliswag: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			env_del(&shell->env, args[i]);
	}
	return (status);
}
