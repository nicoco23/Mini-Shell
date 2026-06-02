/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:35:02 by ltournie          #+#    #+#             */
/*   Updated: 2026/05/07 17:03:38 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_or;

	i = 0;
	j = 0;
	if ((!dst && !src) || !src)
		return (0);
	len_or = ft_strlen(dst);
	if (!dst)
		return (len_or + ft_strlen(src));
	if (size == 0)
		return (size + ft_strlen(src));
	while (dst[i] != '\0')
		i++;
	while (i < (size - 1) && src[j] != '\0')
		dst[i++] = src[j++];
	if (size > len_or)
		dst[i] = '\0';
	if (size > len_or)
		return (len_or + ft_strlen(src));
	else
		return (size + ft_strlen(src));
}
