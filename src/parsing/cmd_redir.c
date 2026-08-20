/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:00:03 by ntassin           #+#    #+#             */
/*   Updated: 2026/08/20 16:10:40 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*new_redir(t_token_type type, char *target, int quoted)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = ft_strdup(target);
	if (!redir->target)
		return (free(redir), NULL);
	redir->quoted = quoted;
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

int	add_redir(t_cmd *cmd, t_token_type type, char *target, int quoted)
{
	t_redir	*redir;
	t_redir	*last;

	redir = new_redir(type, target, quoted);
	if (!redir)
		return (0);
	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return (1);
	}
	last = cmd->redirs;
	while (last->next)
		last = last->next;
	last->next = redir;
	return (1);
}
