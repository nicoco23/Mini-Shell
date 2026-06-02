/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:45:41 by ltournie          #+#    #+#             */
/*   Updated: 2025/12/03 06:10:15 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (ft_lstsize(lst) == 0 || lst == NULL)
		return (0);
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
}
