#include "minishell.h"

static void	run_external(t_cmd *cmd, t_shell *shell)
{
	char	**envp;

	set_path(cmd->args[0], shell->env, cmd);
	if (!cmd->path)
		(print_error(cmd->args[0], 0),	close(STDIN_FILENO), close(STDOUT_FILENO),clean_exit(shell, 127));
	envp = env_to_array(shell->env);
	if (!envp)
		clean_exit(shell, 1);
	execve(cmd->path, cmd->args, envp);
	free_tab(envp);
	print_error(cmd->args[0], 1);
	clean_exit(shell, 126);
}

void	child_process(t_cmd *cmd, t_shell *shell, int in_fd, int *pipe_fd)
{
	int	ret;

	setup_signal_exec();
	if (in_fd != -1)
		(dup2(in_fd, STDIN_FILENO), close(in_fd));
	if (pipe_fd[1] != -1)
		dup2(pipe_fd[1], STDOUT_FILENO);
	close_if_open(pipe_fd[0]);
	close_if_open(pipe_fd[1]);
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
	{
		ret = run_builtin(shell, cmd);
		clean_exit(shell, ret);
	}
	if (apply_redirs(cmd))
		clean_exit(shell, 1);
	run_external(cmd, shell);
}
