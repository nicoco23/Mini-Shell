/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 19:29:58 by ntassin           #+#    #+#             */
/*   Updated: 2026/09/09 21:56:17 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	fork_stage(t_cmd *cmd, t_shell *shell, int in_fd, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_process(cmd, shell, in_fd, pipe_fd);
	return (pid);
}

static int	fork_pipeline(t_shell *shell, pid_t *pids, int i)
{
	t_cmd	*cmd;
	int		in_fd;
	int		pipe_fd[2];

	cmd = shell->cmds;
	in_fd = -1;
	while (cmd)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		if (cmd->next && pipe(pipe_fd) == -1)
			break ;
		pids[i] = fork_stage(cmd, shell, in_fd, pipe_fd);
		if (pids[i] == -1)
		{
			(close_if_open(pipe_fd[0]), close_if_open(pipe_fd[1]));
			break ;
		}
		i++;
		(close_if_open(in_fd), close_if_open(pipe_fd[1]));
		in_fd = pipe_fd[0];
		cmd = cmd->next;
	}
	return (close_if_open(in_fd), i);
}

static void	wait_pipeline(t_shell *shell, pid_t *pids, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		while (waitpid(pids[i], &status, 0) == -1 && errno == EINTR)
			;
		if (i == n - 1)
			update_exit_status(shell, status);
		i++;
	}
	if (shell->last_exit == 130)
		g_signal = SIGINT;
}

// static int	run_builtin_protected(t_shell *shell)
// {
// 	int	stdin_fd;
// 	int	stdout_fd;
// 	int last_exit;

// 	stdin_fd = dup(STDIN_FILENO);
// 	stdout_fd = dup(STDOUT_FILENO);
// 	last_exit = run_builtin(shell, shell->cmds);
// 	dup2(stdin_fd, STDIN_FILENO);
// 	dup2(stdout_fd, STDOUT_FILENO);
// 	close(stdin_fd);
// 	close(stdout_fd);
// 	return (last_exit);
// }

static int	run_builtin_protected(t_shell *shell)
{
	int	last_exit;

	shell->saved_in = dup(STDIN_FILENO);
	shell->saved_out = dup(STDOUT_FILENO);
	if (shell->saved_in == -1 || shell->saved_out == -1)
	{
		close_if_open(shell->saved_in);
		close_if_open(shell->saved_out);
		shell->saved_in = -1;
		shell->saved_out = -1;
		return (1);
	}
	if (!shell->cmds->args || !shell->cmds->args[0])
		last_exit = (apply_redirs(shell->cmds) != 0);
	else
		last_exit = run_builtin(shell, shell->cmds);
	if (dup2(shell->saved_in, STDIN_FILENO) == -1)
		last_exit = 1;
	if (dup2(shell->saved_out, STDOUT_FILENO) == -1)
		last_exit = 1;
	close(shell->saved_in);
	close(shell->saved_out);
	shell->saved_in = -1;
	shell->saved_out = -1;
	return (last_exit);
}

void	exec(t_shell *shell)
{
	pid_t	*pids;
	int		lst_size;
	int		n;

	if (!shell->cmds->next && shell->cmds->args && shell->cmds->args[0]
		&& is_builtin(shell->cmds->args[0]))
	{
		shell->last_exit = run_builtin_protected(shell);
		return ;
	}
	setup_signal_exec2();
	lst_size = ft_listsize_cmd(shell->cmds);
	pids = malloc(sizeof(pid_t) * lst_size);
	if (!pids)
		return ;
	shell->pids = pids;
	n = fork_pipeline(shell, pids, 0);
	if (n > 0)
		wait_pipeline(shell, pids, n);
	if (n < lst_size)
		perror("mouliswag: fork");
	(free(pids), setup_signal_prompt());
	shell->pids = NULL;
}
