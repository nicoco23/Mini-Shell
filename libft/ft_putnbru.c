/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:17:26 by ltournie          #+#    #+#             */
/*   Updated: 2026/04/07 11:29:28 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbru(unsigned int to_write, int nb)
{
	if (to_write < 10)
	{
		nb = ft_putchar((to_write + '0'), nb);
	}
	else if (to_write > 9)
	{
		nb = ft_putnbru((to_write / 10), nb);
		nb = ft_putnbru((to_write % 10), nb);
	}
	return (nb);
}
