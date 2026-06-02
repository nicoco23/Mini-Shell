/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:15:01 by ltournie          #+#    #+#             */
/*   Updated: 2026/05/07 17:03:16 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrhex(unsigned int to_write, int nb, char c)
{
	char	*base;

	if (c == 'U')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (to_write < 16)
	{
		c = base[to_write];
		nb = ft_putchar(c, nb);
	}
	if (to_write > 15)
	{
		nb = ft_putnbrhex((to_write / 16), nb, c);
		nb = ft_putnbrhex((to_write % 16), nb, c);
	}
	return (nb);
}
