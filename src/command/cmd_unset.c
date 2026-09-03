#include "minishell.h"

char	**env_copy_del(char **env, int *n)
{
	char	**cp;
	int		i;
	int		n;

	*n = env_count(env);
	cp = malloc(sizeof(char *) * (*n - 1));
	if (!cp)
		return (NULL);
	i = -1;
	while (++i < *n)
		cp[i] = env[i];
	cp[*n] = NULL;
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

int	delete_line(int nb, char ***env)
{

}

int cmd_unset(char **args, t_shell *shell)
{
	int val;
	char **cp;

	val = check_args(args, shell->env);
	if (val == -1)
		return (0);
	cp = sort_env_copy(shell->env, val);
	if (cp == NULL)
		return (1);
	free_shell();
	return (0);
}