/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 12:51:32 by ntassin           #+#    #+#             */
/*   Updated: 2026/08/19 12:52:19 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_cmds(t_cmd *cmds)
{
	t_redir	*r;
	int		i;

	while (cmds)
	{
		printf("CMD: ");
		i = 0;
		if (!cmds->args || !cmds->args[0])
			printf("(vide, args[0]==NULL)");
		while (cmds->args && cmds->args[i])
			printf("[%s] ", cmds->args[i++]);
		r = cmds->redirs;
		while (r)
		{
			printf("| redir(type=%d, target=%s) ", r->type, r->target);
			r = r->next;
		}
		printf("\n");
		cmds = cmds->next;
	}
}
