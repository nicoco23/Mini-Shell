#include "minishell.h"

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	return (ft_strncmp(name, "cd", 3) == 0
		|| ft_strncmp(name, "pwd", 4) == 0
		|| ft_strncmp(name, "echo", 5) == 0
		|| ft_strncmp(name, "env", 4) == 0
		|| ft_strncmp(name, "export", 7) == 0
		|| ft_strncmp(name, "unset", 6) == 0
		|| ft_strncmp(name, "exit", 5) == 0);
}

static int	dispatch_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*name;

	if (!cmd->args || !cmd->args[0])
		return (0);
	name = cmd->args[0];
	if (ft_strncmp(name, "cd", 3) == 0)
		return (cmd_cd(shell, cmd));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (cmd_pwd());
	if (ft_strncmp(name, "echo", 5) == 0)
		return (cmd_echo(cmd->args));
	if (ft_strncmp(name, "env", 4) == 0)
		return (cmd_env(shell->env));
	if (ft_strncmp(name, "exit", 5) == 0)
		return (cmd_exit(shell, cmd->args));
	if (ft_strncmp(name, "export", 7) == 0)
		return (cmd_export(shell, cmd->args));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (cmd_unset(cmd->args, shell));
	return (0);
}

int	run_builtin(t_shell *shell, t_cmd *cmd)
{
	int	ret;

	shell->saved_in = dup(STDIN_FILENO);
	shell->saved_out = dup(STDOUT_FILENO);
	if (apply_redirs(cmd))
		ret = 1;
	else
		ret = dispatch_builtin(shell, cmd);
	dup2(shell->saved_in, STDIN_FILENO);
	dup2(shell->saved_out, STDOUT_FILENO);
	close(shell->saved_in);
	close(shell->saved_out);
	shell->saved_in = -1;
	shell->saved_out = -1;
	return (ret);
}
