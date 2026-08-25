/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 19:29:58 by ntassin           #+#    #+#             */
/*   Updated: 2026/08/25 20:16:43 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_cmd *cmd, char **envp, int in_fd, int *pipe_fd)
{
	setup_signal_exec();
	if (in_fd != -1)
		(dup2(in_fd, STDIN_FILENO), close(in_fd));
	if (pipe_fd[1] != -1)
		dup2(pipe_fd[1], STDOUT_FILENO);
	close_if_open(pipe_fd[0]);
	close_if_open(pipe_fd[1]);
	if (apply_redirs(cmd))
		(free_cmds(cmd), exit(1));
	set_path(cmd->args[0], envp, cmd);
	if (!cmd->path)
		(print_error(cmd->args[0], 0), free_cmds(cmd), exit(127));
	execve(cmd->path, cmd->args, envp);
	print_error(cmd->args[0], 1);
	(free_cmds(cmd), exit(126));
}

static int	fork_pipeline(t_shell *shell, pid_t *pids)
{
	t_cmd	*cmd;
	int		in_fd;
	int		pipe_fd[2];
	int		i;
	pid_t	pid;

	cmd = shell->cmds;
	in_fd = -1;
	i = 0;
	while (cmd)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		if (cmd->next && pipe(pipe_fd) == -1)
			return (-1);
		pid = fork();
		if (pid == 0)
			child_process(cmd, shell->env, in_fd, pipe_fd);
		pids[i++] = pid;
		close_if_open(in_fd);
		close_if_open(pipe_fd[1]);
		in_fd = pipe_fd[0];
		cmd = cmd->next;
	}
	return (i);
}

static void	wait_pipeline(t_shell *shell, pid_t *pids, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (i == n - 1)
			update_exit_status(shell, status);
		i++;
	}
}

void	exec(t_shell *shell)
{
	pid_t	*pids;
	int		lst_size;
	int		n;

	lst_size = ft_listsize_cmd(shell->cmds);
	pids = malloc(sizeof(pid_t) * lst_size);
	if (!pids)
		return ;
	setup_signal_wait();
	n = fork_pipeline(shell, pids);
	if (n != -1)
		wait_pipeline(shell, pids, n);
	setup_signal_prompt();
	g_signal = 0;
	free(pids);
}
