/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:18:00 by ltournie          #+#    #+#             */
/*   Updated: 2026/05/07 01:00:32 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordplan(char *str, char c, char o)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (o == 'l')
		return (i);
	else
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		return (i);
	}
}

static char	**ft_mallocempty(void)
{
	char	**list;

	list = malloc(sizeof(char *) * 1);
	if (!list)
		return (NULL);
	list[0] = NULL;
	return (list);
}

static char	**ft_mallocstr(char **list, char *str, int cw, char c)
{
	int	i;
	int	strp;

	i = 0;
	strp = 0;
	while (i < cw)
	{
		list[i] = ft_substr(str, (unsigned int)strp,
				(size_t)ft_wordplan(&str[strp], c, 'l'));
		if (!list[i])
		{
			while (i > -1)
				free(list[i--]);
			free(list);
			return (NULL);
		}
		i++;
		strp = strp + ft_wordplan(&str[strp], c, 'n');
	}
	list[cw] = NULL;
	return (list);
}

char	**ft_split(char const *s, char c)
{
	char		**array;
	int			cw;
	char		*str;
	const char	str2[2] = {c, '\0'};

	if (!s)
		return (NULL);
	str = ft_strtrim(s, str2);
	if (!str)
		return (NULL);
	cw = ft_countword(str, c);
	if (ft_strlen(s) == 0 || ft_strlen(str) == 0 || cw == 0)
	{
		array = ft_mallocempty();
		if (array == NULL)
			return (free(str), free(array), NULL);
		return (free(str), array);
	}
	array = malloc(sizeof(char *) * (cw + 1));
	if (!array)
		return (free(str), free(array), NULL);
	array = ft_mallocstr(array, str, cw, c);
	return (free(str), array);
}
