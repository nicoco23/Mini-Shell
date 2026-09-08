/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:50:47 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/08 13:50:48 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_update(t_env *node, char *value, int visibility)
{
	char	*dup;

	if (visibility)
		node->visibility = 1;
	if (!value)
		return (0);
	dup = ft_strdup(value);
	if (!dup)
		return (1);
	free(node->value);
	node->value = dup;
	return (0);
}

int	env_put(t_env **lst, char *name, char *value, int visibility)
{
	t_env	*node;

	node = env_find(*lst, name);
	if (node)
		return (env_update(node, value, visibility));
	node = env_new(name, value, visibility);
	if (!node)
		return (1);
	return (env_add_back(lst, node), 0);
}

/* entry = "NAME=VALUE" ou "NAME" */
int	env_put_entry(t_env **lst, char *entry, int visibility)
{
	char	*eq;
	char	*name;
	int		ret;

	eq = ft_strchr(entry, '=');
	if (!eq)
		return (env_put(lst, entry, NULL, visibility));
	name = ft_substr(entry, 0, eq - entry);
	if (!name)
		return (1);
	ret = env_put(lst, name, eq + 1, visibility);
	return (free(name), ret);
}

void	env_del(t_env **lst, const char *name)
{
	t_env	*cur;
	t_env	*prev;

	prev = NULL;
	cur = *lst;
	while (cur)
	{
		if (ft_strncmp(cur->name, name, ft_strlen(name) + 1) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*lst = cur->next;
			return ((void)(free(cur->name), free(cur->value), free(cur)));
		}
		prev = cur;
		cur = cur->next;
	}
}
