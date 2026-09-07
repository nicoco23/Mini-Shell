#include "minishell.h"

static void	init_shlvl(t_shell *shell)
{
	char	*val;
	char	*nb;
	int		lvl;

	lvl = 1;
	val = get_env_value(shell->env, "SHLVL");
	if (val)
		lvl = ft_atoi(val) + 1;
	if (lvl < 1)
		lvl = 1;
	nb = ft_itoa(lvl);
	if (!nb)
		return ;
	env_set_kv(shell, "SHLVL", nb);
	free (nb);
}

void	init_shell_env(t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (!get_env_value(shell->env, "PWD") && getcwd(cwd, PATH_MAX))
		env_set_kv(shell, "PWD", cwd);
	init_shlvl(shell);
}
