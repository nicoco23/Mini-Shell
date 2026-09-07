#include "minishell.h"

int	cmd_env(char **env)
{
	int	i;

	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '=') && putendl_check(env[i], 1))
			return (write_error("env"), 1);
		i++;
	}
	return (0);
}
