#include "minishell.h"

static int	env_cmp(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && a[i] == b[i])
		i++;
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

static void	bubble(char **cp, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < n - 1)
	{
		j = -1;
		while (++j < n - 1 - i)
		{
			if (env_cmp(cp[j], cp[j + 1]) > 0)
			{
				tmp = cp[j];
				cp[j] = cp[j + 1];
				cp[j + 1] = tmp;
			}
		}
	}
}

char	**sort_env_copy(char **env, int *n)
{
	char	**cp;
	int		i;

	*n = env_count(env);
	cp = malloc(sizeof(char *) * (*n + 1));
	if (!cp)
		return (NULL);
	i = -1;
	while (++i < *n)
		cp[i] = env[i];
	cp[*n] = NULL;
	bubble(cp, *n);
	return (cp);
}
