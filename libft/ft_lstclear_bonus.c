/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 01:47:04 by ltournie          #+#    #+#             */
/*   Updated: 2025/12/03 06:18:17 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*temp;

	if (lst == NULL)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		temp = ptr->next;
		ft_lstdelone((ptr), del);
		ptr = temp;
	}
	*lst = NULL;
}
