/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:52:25 by ltournie          #+#    #+#             */
/*   Updated: 2025/11/26 19:45:16 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	minuscheck(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static int	numlen(int n, int i)
{
	int		len;
	long	res;

	len = 1;
	res = n;
	if (i == 1)
	{
		len++;
		res = -res;
	}
	while (res > 9)
	{
		res = res / 10;
		len++;
	}
	return (len);
}

static long	convertdigit(char *str, long res, int len)
{
	str[len] = res % 10 + '0';
	if (res > 9)
		res = res / 10;
	return (res);
}

char	*ft_itoa(int n)
{
	long	res;
	char	*str;
	int		len;
	int		i;

	i = minuscheck(n);
	res = n;
	len = numlen(n, i);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (i == 1)
	{
		str[0] = '-';
		res = -res;
	}
	str[len] = '\0';
	while (--len >= 0)
	{
		if ((len) == 0 && i == 1)
			return (str);
		res = convertdigit(str, res, len);
	}
	return (str);
}
