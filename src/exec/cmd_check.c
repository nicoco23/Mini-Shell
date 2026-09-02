#include "minishell.h"

int check_cmd(t_cmd *cmds, char **env)
{
	if (ft_strncmp (cmds->args[0], "cd\0", 3) == 0)
		return (cmd_cd(cmds), 0);
	if (ft_strncmp (cmds->args[0], "pwd\0", 4) == 0)
		return (cmd_pwd(), 0);
	if (ft_strncmp(cmds->args[0], "echo\0", 5) == 0)
		return (cmd_echo(cmds->args), 0);
	if (ft_strncmp(cmds->args[0], "env\0", 4) == 0)
		return (cmd_env(env), 0);
	else
		return (1);
}

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	return (ft_strncmp(name, "cd\0", 3) == 0
		|| ft_strncmp(name, "pwd\0", 4) == 0
		|| ft_strncmp(name, "echo\0", 5) == 0
		|| ft_strncmp(name, "env\0", 4) == 0
		|| ft_strncmp(name, "export\0", 7) == 0
		|| ft_strncmp(name, "unset\0", 6) == 0
		|| ft_strncmp(name, "exit\0", 5) == 0);
}

static int	dispatch_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*name;

	name = cmd->args[0];
	if (ft_strncmp(name, "cd\0", 3) == 0)
		return (cmd_cd(cmd));
	if (ft_strncmp(name, "pwd\0", 4) == 0)
		return (cmd_pwd());
	if (ft_strncmp(name, "echo\0", 5) == 0)
		return (cmd_echo(cmd->args));
	if (ft_strncmp(name, "env\0", 4) == 0)
		return (cmd_env(shell->env));
	if (strncmp(name, "exit\0", 5) == 0)
		return (cmd_exit(shell, cmd->args));
	return (0);
}

int	run_builtin_parent(t_shell *shell, t_cmd *cmd)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirs(cmd))
		ret = 1;
	else
		ret = dispatch_builtin(shell, cmd);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (ret);
}
