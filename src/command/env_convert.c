#include "minishell.h"

#include "minishell.h"

int	env_size(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static int	env_export_count(t_env *lst)
{
	int	n;

	n = 0;
	while (lst)
	{
		if (lst->visibility && lst->value)
			n++;
		lst = lst->next;
	}
	return (n);
}

static char	*env_join(t_env *node)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(node->name, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, node->value);
	free(tmp);
	return (res);
}

char	**env_to_array(t_env *lst)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (env_export_count(lst) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (lst->visibility && lst->value)
		{
			tab[i] = env_join(lst);
			if (!tab[i])
				return (free_tab(tab), NULL);
			i++;
		}
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	env_from_envp(char **envp, t_env **out)
{
	int	i;

	*out = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (env_put_entry(out, envp[i], 1))
			return (env_clear(out), 1);
		i++;
	}
	return (0);
}
