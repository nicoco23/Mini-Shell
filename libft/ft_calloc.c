/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:45:29 by ltournie          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:36 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*list;

	if (nmemb == 0 || size == 0)
	{
		list = malloc(0);
		if (!list)
			return (NULL);
		return (list);
	}
	if ((nmemb * size) >= 2147483647 || (int)nmemb < 0 || (int)size < 0
		|| nmemb >= SIZE_MAX || size >= SIZE_MAX)
		return (NULL);
	else
	{
		list = malloc(nmemb * size);
		if (!list)
			return (NULL);
		ft_bzero(list, (nmemb * size));
	}
	return (list);
}
