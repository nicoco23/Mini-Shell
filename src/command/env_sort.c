#include "minishell.h"

static int	env_cmp(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && a[i] == b[i])
		i++;
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

static void	bubble(t_env **cp, int n)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < n - 1)
	{
		j = -1;
		while (++j < n - 1 - i)
		{
			if (env_cmp(cp[j]->name, cp[j + 1]->name) > 0)
			{
				tmp = cp[j];
				cp[j] = cp[j + 1];
				cp[j + 1] = tmp;
			}
		}
	}
}

t_env	**sort_env_copy(t_env *lst, int *n)
{
	t_env	**cp;
	int		i;

	*n = env_size(lst);
	cp = malloc(sizeof(t_env *) * (*n + 1));
	if (!cp)
		return (NULL);
	i = 0;
	while (lst)
	{
		cp[i++] = lst;
		lst = lst->next;
	}
	cp[*n] = NULL;
	bubble(cp, *n);
	return (cp);
}
