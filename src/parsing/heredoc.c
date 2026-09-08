/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:36:55 by ntassin           #+#    #+#             */
/*   Updated: 2026/09/08 12:03:12 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_loop(int fd, char *delim)
{
	char	*line;
	int		savec_stdin;

	savec_stdin = dup(STDIN_FILENO);
	line = readline("> ");
	while (line && g_signal != SIGINT)
	{
		if (ft_strlen(line) == ft_strlen(delim)
			&& !ft_strncmp(line, delim, ft_strlen(delim)))
		{
			free(line);
			return (close(savec_stdin), 0);
		}
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	free(line);
	if (g_signal == SIGINT)
		dup2(savec_stdin, STDIN_FILENO);
	return (close(savec_stdin), -1);
}

static int	read_one_heredoc(t_redir *redir)
{
	int	pipe_fd[2];

	dprintf(2,"cc\n");
	setup_signal_heredoc();
	if (pipe(pipe_fd) == -1)
		return (-1);
	if (heredoc_loop(pipe_fd[1], redir->target) == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	close(pipe_fd[1]);
	redir->fd_pipe[0] = pipe_fd[0];
	return (0);
}

int	read_heredocs(t_cmd *cmds)
{
	t_redir	*redir;
	int		interrupted;

	interrupted = 0;
	while (cmds && !interrupted)
	{
		redir = cmds->redirs;
		while (redir && !interrupted)
		{
			if (redir->type == TOKEN_REDIR_HEREDOC
				&& read_one_heredoc(redir) == -1)
				interrupted = 1;
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	g_signal = 0;
	return (interrupted);
}
