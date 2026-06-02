/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:09:53 by ltournie          #+#    #+#             */
/*   Updated: 2025/12/03 06:18:45 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

	if (new == NULL)
		return ;
	if ((*lst) == NULL)
	{
		*lst = new;
		return ;
	}
	list = *lst;
	while ((list)->next != NULL)
		(list) = (list)->next;
	(list)->next = new;
}
