#include "minishell.h"

char	**env_copy_del(char **env, int val)
{
	char	**cp;
	int		i;
	int		n;

	n = env_count(env);
	cp = malloc(sizeof(char *) * (n));
	if (!cp)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		if (i == val)
			i++;
		cp[i] = env[i];
	}
	cp[n] = NULL;
	free_tab(env);
	return (cp);
}

int check_args(char **env, char *arg)
{
	int i;

	i = 0;
	while(env[i] != NULL)
	{
		if (ft_strncmp(env[i], arg, (ft_strlen(arg) + 1) ) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int cmd_unset(char **args, t_shell *shell)
{
	int val;
	char **cp;

	val = check_args(shell->env, args[1]);
	if (val == -1)
		return (0);
	cp = env_copy_del(shell->env, val);
	if (cp == NULL)
		return (1);
	return (0);
}