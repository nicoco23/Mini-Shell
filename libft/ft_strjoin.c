/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:03:01 by ltournie          #+#    #+#             */
/*   Updated: 2025/11/27 18:21:59 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s2 && !s1)
		return (NULL);
	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	if (ft_strlen(s1) == 0 && ft_strlen(s2) == 0)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * ((ft_strlen(s1)) + (ft_strlen(s2)) + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, (ft_strlen(s1) + 1));
	ft_strlcat(str, s2, ((ft_strlen(s1)) + (ft_strlen(s2)) + 1));
	return (str);
}
