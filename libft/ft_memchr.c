/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:55:48 by ltournie          #+#    #+#             */
/*   Updated: 2025/11/27 17:35:33 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	const char		*str;
	unsigned char	d;

	i = 0;
	str = (const char *) s;
	d = (unsigned char) c;
	if (!s)
		return (NULL);
	while (i < n)
	{
		if ((unsigned char)str[i] == d)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
