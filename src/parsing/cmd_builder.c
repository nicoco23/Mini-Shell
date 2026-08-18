/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:55:54 by ntassin           #+#    #+#             */
/*   Updated: 2026/08/17 18:42:22 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*new_cmd(void)
{
	return (ft_calloc(1, sizeof(t_cmd)));
}

static int	count_segment(t_token *start)
{
	int	count;

	count = 0;
	while (start && start->type != TOKEN_PIPE)
	{
		count++;
		start = start->next;
	}
	return (count);
}

static int	fill_cmd(t_cmd *cmd, t_token **tokens)
{
	t_token	*cur;
	int		i;

	cmd->args = ft_calloc(count_segment(*tokens) + 1, sizeof(char *));
	if (!cmd->args)
		return (0);
	cur = *tokens;
	i = 0;
	while (cur && cur->type != TOKEN_PIPE)
	{
		if (cur->type == TOKEN_WORD)
		{
			cmd->args[i] = ft_strdup(cur->value);
			if (!cmd->args[i++])
				return (0);
			cur = cur->next;
		}
		else
		{
			if (!add_redir(cmd, cur->type, cur->next->value))
				return (0);
			cur = cur->next->next;
		}
	}
	return (*tokens = cur, 1);
}

t_cmd	*build_cmds(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*last;
	t_cmd	*cmd;

	head = NULL;
	last = NULL;
	while (tokens)
	{
		cmd = new_cmd();
		if (!cmd || !fill_cmd(cmd, &tokens))
			return (free_cmds(cmd), free_cmds(head), NULL);
		if (!head)
			head = cmd;
		else
			last->next = cmd;
		last = cmd;
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (head);
}
