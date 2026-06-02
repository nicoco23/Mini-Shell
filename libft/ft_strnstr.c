/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:32:57 by ltournie          #+#    #+#             */
/*   Updated: 2026/05/07 17:14:34 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!big)
		return (NULL);
	if (ft_strlen(little) == 0 || little == NULL)
		return ((char *) big);
	while (i <= len && big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			if ((ft_strncmp(&big[i], little, ft_strlen(little)) == 0)
				&& ((i + ft_strlen(little)) <= len))
				return ((char *) &big[i]);
		}
		i++;
	}
	return (NULL);
}
