#include "minishell.h"

int	env_set_kv(t_shell *shell, char *name, char *value)
{
	char	*tmp;
	char	*entry;
	int		ret;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (1);
	entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!entry)
		return (1);
	ret = env_set(shell, entry);
	return (free(entry), ret);
}

void	env_remove_at(char **env, int idx)
{
	free(env[idx]);
	while (env[idx + 1])
	{
		env[idx] = env[idx + 1];
		idx++;
	}
	env[idx] = NULL;
}
