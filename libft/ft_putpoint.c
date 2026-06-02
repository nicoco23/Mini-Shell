/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:43:33 by ltournie          #+#    #+#             */
/*   Updated: 2026/04/07 11:29:28 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putpoint(unsigned long arg, int nb)
{
	char	*nil;

	nil = "(nil)";
	if (arg == 0)
	{
		nb = ft_putstr(nil, nb);
		return (nb);
	}
	nb = ft_putchar('0', nb);
	nb = ft_putchar('x', nb);
	nb = ft_putnbrhexp(arg, nb);
	return (nb);
}
