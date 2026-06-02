/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:42:02 by ltournie          #+#    #+#             */
/*   Updated: 2026/04/17 13:41:57 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *) s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return ((void *) str);
}
