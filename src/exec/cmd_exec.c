/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 19:29:58 by ntassin           #+#    #+#             */
/*   Updated: 2026/09/08 12:13:11 by ltournie         ###   ########.fr       */
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

static int	fork_pipeline(t_shell *shell, pid_t *pids)
{
	t_cmd	*cmd;
	int		in_fd;
	int		pipe_fd[2];
	int		i;

	cmd = shell->cmds;
	in_fd = -1;
	i = 0;
	while (cmd)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		if (cmd->next && pipe(pipe_fd) == -1)
			break ;
		pids[i] = fork_stage(cmd, shell, in_fd, pipe_fd);
		if (pids[i] == -1)
		{
			close_if_open(pipe_fd[0]);
			close_if_open(pipe_fd[1]);
			break ;
		}
		i++;
		close_if_open(in_fd);
		close_if_open(pipe_fd[1]);
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
}

void	exec(t_shell *shell)
{
	pid_t	*pids;
	int		lst_size;
	int		n;

	if (!shell->cmds->next && shell->cmds->args && shell->cmds->args[0]
		&& is_builtin(shell->cmds->args[0]))
	{
		shell->last_exit = run_builtin(shell, shell->cmds);
		return ;
	}
	setup_signal_exec();
	lst_size = ft_listsize_cmd(shell->cmds);
	pids = malloc(sizeof(pid_t) * lst_size);
	if (!pids)
		return ;
	shell->pids = pids;
	// setup_signal_wait();
	n = fork_pipeline(shell, pids);
	if (n > 0)
	{
		setup_signal_exec2();
		wait_pipeline(shell, pids, n);
	}
	if (n < lst_size)
		perror("mouliswag: fork");
	g_signal = 0;
	free(pids);
	shell->pids = NULL;
	setup_signal_prompt();
}
