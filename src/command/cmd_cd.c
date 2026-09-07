#include "minishell.h"

static void	cwd_error(char *who)
{
	ft_putstr_fd("mouliswag: ", 2);
	ft_putstr_fd(who, 2);
	ft_putstr_fd(": error retrieving current directory: getcwd: "
		"cannot access parent directories: "
		"No such file or directory\n", 2);
}

static void	update_pwd(t_shell *shell, char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (oldpwd)
		env_set_kv(shell, "OLDPWD", oldpwd);
	if (getcwd(cwd, PATH_MAX))
		env_set_kv(shell, "PWD", cwd);
	else
		cwd_error("cd");
}

static char	*cd_target(t_shell *shell, char **args)
{
	char	*home;

	if (args[1])
		return (args[1]);
	home = get_env_value(shell->env, "HOME");
	if (!home || !home[0])
		return (ft_putstr_fd("mouliswag: cd: HOME not set\n", 2), NULL);
	return (home);
}

int	cmd_cd(t_shell *shell, t_cmd *cmd)
{
	char	buf[PATH_MAX];
	char	*path;
	char	*old;

	if (cmd->args[1] && cmd->args[2])
		return (ft_putstr_fd("mouliswag: cd: too many arguments\n", 2), 1);
	if (cmd->args[1] && !cmd->args[1][0])
		return (0);
	path = cd_target(shell, cmd->args);
	if (!path)
		return (1);
	old = getcwd(buf, PATH_MAX);
	if (!old)
		old = get_env_value(shell->env, "PWD");
	if (chdir(path) != 0)
	{
		ft_putstr_fd("mouliswag: cd: ", 2);
		return (perror(path), 1);
	}
	return (update_pwd(shell, old), 0);
}
