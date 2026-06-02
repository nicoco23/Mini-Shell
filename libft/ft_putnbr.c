/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:17:26 by ltournie          #+#    #+#             */
/*   Updated: 2026/04/07 11:29:28 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int to_write, int nb)
{
	char	c;

	if (to_write == -2147483648)
	{
		write(1, "-2147483648", 11);
		nb += 11;
		return (nb);
	}
	if (to_write < 0)
	{
		nb = ft_putchar('-', nb);
		to_write *= -1;
	}
	if (to_write < 10)
	{
		c = to_write + '0';
		nb = ft_putchar(c, nb);
	}
	if (to_write > 9)
	{
		nb = ft_putnbr((to_write / 10), nb);
		nb = ft_putnbr((to_write % 10), nb);
	}
	return (nb);
}
