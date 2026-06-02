/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:15:17 by ltournie          #+#    #+#             */
/*   Updated: 2026/04/07 11:29:28 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str, int nb)
{
	int		i;
	char	*str2;

	i = -1;
	str2 = "(null)";
	if (str == NULL)
	{
		while (str2[++i] != '\0')
			nb = ft_putchar(str2[i], nb);
		return (nb);
	}
	while (str[++i] != '\0')
		nb = ft_putchar(str[i], nb);
	return (nb);
}
