/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:22:45 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/08 16:39:08 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if ((char)c == '\0')
		return ((char *) &s[ft_strlen(s)]);
	while (s && s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *) &s[i]);
		else
			i++;
	}
	return (NULL);
}
