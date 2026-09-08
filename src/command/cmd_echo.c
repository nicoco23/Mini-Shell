/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:50:27 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/08 13:52:00 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag_n(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	cmd_echo(char **args)
{
	int	i;
	int	k;
	int	newline;

	newline = 1;
	i = 1;
	k = 0;
	while (args[i] && is_flag_n(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		k += ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			k += ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		k += ft_putstr_fd("\n", 1);
	if (k < 0)
		return (write(2, "echo: write error: No space left on device\n"\
, 44) - 42);
	return (0);
}
