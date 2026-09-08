#include "minishell.h"

static void	init_shlvl(t_shell *shell)
{
	char	*val;
	char	*nb;
	int		lvl;

	lvl = 1;
	val = env_get(shell->env, "SHLVL");
	if (val)
		lvl = ft_atoi(val) + 1;
	if (lvl < 1)
		lvl = 1;
	nb = ft_itoa(lvl);
	if (!nb)
		return ;
	env_put(&shell->env, "SHLVL", nb, 1);
	free (nb);
}

void	init_shell_env(t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (!env_get(shell->env, "PATH"))
		env_put(&shell->env, "PATH", DEFAULT_PATH, 0);
	if (!env_get(shell->env, "PWD") && getcwd(cwd, PATH_MAX))
		env_put(&shell->env, "PWD", cwd, 1);
	init_shlvl(shell);
}
