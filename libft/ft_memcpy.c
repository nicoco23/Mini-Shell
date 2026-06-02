/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:03:35 by ltournie          #+#    #+#             */
/*   Updated: 2025/11/26 19:46:13 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest_char;
	const char	*src_char;

	if (!src)
		return (dest);
	if (!dest)
		return (NULL);
	i = 0;
	dest_char = (char *) dest;
	src_char = (const char *) src;
	while (i < n)
	{
		dest_char[i] = src_char[i];
		i++;
	}
	return (dest);
}
