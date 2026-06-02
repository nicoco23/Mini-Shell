/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:27:07 by ltournie          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:06 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (!nptr)
		return (0);
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (!(ft_strncmp(&nptr[i], "-2147483648", 11)))
		return (-2147483648);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while ((ft_isdigit(nptr[i])))
		res = res * 10 + (nptr[i++] - '0');
	if (res > 2147483647 || res < -2147483648)
		return (0);
	return ((int)res * sign);
}
