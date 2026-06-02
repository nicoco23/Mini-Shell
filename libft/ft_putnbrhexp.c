/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:15:01 by ltournie          #+#    #+#             */
/*   Updated: 2026/05/07 17:03:21 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrhexp(unsigned long to_write, int nb)
{
	char	*base;
	char	c;

	base = "0123456789abcdef";
	if (to_write < 16)
	{
		c = base[to_write];
		nb = ft_putchar(c, nb);
	}
	if (to_write > 15)
	{
		nb = ft_putnbrhexp((to_write / 16), nb);
		nb = ft_putnbrhexp((to_write % 16), nb);
	}
	return (nb);
}
