/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:52:25 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/09 22:04:28 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_is_dir(t_shell *shell, char *path, char *name)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("mouliswag: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		clean_exit(shell, 126);
	}
}

static void	run_external(t_cmd *cmd, t_shell *shell)
{
	char	**envp;
	int		err;

	set_path(cmd->args[0], shell->env, cmd);
	if (!cmd->path)
		(print_error(cmd->args[0], 0), clean_exit(shell, 127));
	check_is_dir(shell, cmd->path, cmd->args[0]);
	envp = env_to_array(shell->env);
	if (!envp)
		clean_exit(shell, 1);
	execve(cmd->path, cmd->args, envp);
	err = errno;
	free_tab(envp);
	errno = err;
	print_error(cmd->args[0], 1);
	if (err == ENOENT)
		clean_exit(shell, 127);
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
	if (!cmd->args || !cmd->args[0])
		clean_exit(shell, 0);
	run_external(cmd, shell);
}
