/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:20:38 by ltournie          #+#    #+#             */
/*   Updated: 2025/11/28 14:55:18 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s) || ft_strlen(s) == 0 || len == 0)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	else if (ft_strlen(&s[start]) < len)
		str = malloc(sizeof(char) * (ft_strlen(&s[start]) + 1));
	else
		str = malloc(sizeof(char) * (len) + 1);
	if (!str)
		return (NULL);
	if (ft_strlen(&s[start]) < len)
		ft_strlcpy(str, &s[start], ft_strlen(&s[start]) + 1);
	else
		ft_strlcpy(str, &s[start], len + 1);
	return (str);
}
