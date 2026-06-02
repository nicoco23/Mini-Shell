/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:29:39 by ltournie          #+#    #+#             */
/*   Updated: 2025/11/26 19:15:12 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkset(const char *set, const char *s1, char sign)
{
	int		first;
	int		last;

	first = 0;
	last = (ft_strlen(s1) - 1);
	if (sign == '+')
	{
		while (ft_strchr(set, s1[first]) != NULL && s1[first] != '\0')
			first++;
		return (first);
	}
	if (sign == '-')
	{
		while (ft_strrchr(set, s1[last]) != NULL && last >= 0)
			last--;
		return (last);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		first;
	int		last;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	first = checkset(set, s1, '+');
	if (first >= (int)ft_strlen(s1))
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	last = checkset(set, s1, '-') + 1;
	str = malloc(sizeof(char) * (last - first + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[first], (last - first + 1));
	return (str);
}
