#include "minishell.h"

t_env	*env_new(char *name, char *value, int visibility)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	node->value = NULL;
	if (value)
		node->value = ft_strdup(value);
	if (!node->name || (value && !node->value))
		return (free(node->name), free(node->value), free(node), NULL);
	node->visibility = visibility;
	node->next = NULL;
	return (node);
}

t_env	*env_find(t_env *lst, const char *name)
{
	while (lst)
	{
		if (ft_strncmp(lst->name, name, ft_strlen(name) + 1) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

char	*env_get(t_env *lst, const char *name)
{
	t_env	*node;

	node = env_find(lst, name);
	if (!node)
		return (NULL);
	return (node->value);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*cur;

	if (!*lst)
		return ((void)(*lst = new));
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	env_clear(t_env **lst)
{
	t_env	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->name);
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}
