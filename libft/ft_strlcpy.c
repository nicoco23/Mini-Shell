/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:17:25 by ltournie          #+#    #+#             */
/*   Updated: 2025/11/26 19:31:21 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	if (!src)
		return (0);
	src_len = ft_strlen(src);
	if (n == 0 || dest == NULL)
		return (src_len);
	while (i < (n - 1) && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (n > 0)
		dest[i] = '\0';
	return (src_len);
}
