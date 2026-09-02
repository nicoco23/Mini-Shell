#include "minishell.h"

int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	env_index(char **env, const char *name)
{
	int	i;
	int	nlen;

	nlen = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], name, nlen) == 0
			&& (env[i][nlen] == '=' || env[i][nlen] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static int	env_replace(char **env, int idx, const char *entry)
{
	char	*dup;

	dup = ft_strdup(entry);
	if (!dup)
		return (1);
	free(env[idx]);
	env[idx] = dup;
	return (0);
}

static int	env_append(t_shell *shell, const char *entry)
{
	char	**new;
	int		i;
	int		n;

	n = env_count(shell->env);
	new = malloc(sizeof(char *) * (n + 2));
	if (!new)
		return (1);
	i = -1;
	while (++i < n)
		new[i] = shell->env[i];
	new[n] = ft_strdup(entry);
	new[n + 1] = NULL;
	if (!new[n])
		return (free(new), 1);
	free(shell->env);
	shell->env = new;
	return (0);
}

int	env_set(t_shell *shell, const char *entry)
{
	char	*name;
	int		idx;
	int		nlen;

	nlen = 0;
	while (entry[nlen] && entry[nlen] != '=')
		nlen++;
	name = ft_substr(entry, 0, nlen);
	if (!name)
		return (1);
	idx = env_index(shell->env, name);
	free(name);
	if (idx >= 0)
		return (env_replace(shell->env, idx, entry));
	return (env_append(shell, entry));
}
