/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:27:50 by ltournie          #+#    #+#             */
/*   Updated: 2025/11/26 19:38:38 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*memdest;
	unsigned char	*memsrc;

	if ((!dest && !src) || !dest)
		return (NULL);
	if (!src)
		return (dest);
	memdest = (unsigned char *)dest;
	memsrc = (unsigned char *)src;
	i = -1;
	if (memdest < memsrc)
	{
		while (++i < n)
			memdest[i] = memsrc[i];
	}
	else
	{
		while (n--)
		{
			memdest[n] = memsrc[n];
		}
	}
	return (dest);
}
