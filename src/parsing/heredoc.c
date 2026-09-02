/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:36:55 by ntassin           #+#    #+#             */
/*   Updated: 2026/09/09 14:30:25 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_hd_tmp(char **path_out)
{
	char	*nb;
	char	*path;
	int		seq;
	int		fd;

	seq = 0;
	fd = -1;
	while (fd == -1 && seq < 10000)
	{
		nb = ft_itoa(seq++);
		if (!nb)
			return (-1);
		path = ft_strjoin("/tmp/.mouliswag_hd_", nb);
		free(nb);
		if (!path)
			return (-1);
		fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd == -1)
			free(path);
	}
	if (fd == -1)
		return (-1);
	return (*path_out = path, fd);
}

static int	read_one_heredoc(t_redir *redir, t_shell *shell)
{
	char	*path;
	int		wfd;
	int		rfd;
	int		ret;

	setup_signal_heredoc();
	path = NULL;
	wfd = open_hd_tmp(&path);
	if (wfd == -1)
		return (perror("mouliswag: heredoc"), -2);
	ret = heredoc_loop(wfd, redir, shell);
	close(wfd);
	if (ret != 0)
		return (unlink(path), free(path), ret);
	rfd = open(path, O_RDONLY);
	unlink(path);
	free(path);
	if (rfd == -1)
		return (perror("mouliswag: heredoc"), -2);
	return (redir->fd_pipe[0] = rfd, 0);
}

static int	hd_list(t_redir *redir, t_shell *shell)
{
	int	ret;

	while (redir)
	{
		if (redir->type == TOKEN_REDIR_HEREDOC)
		{
			ret = read_one_heredoc(redir, shell);
			if (ret != 0)
				return (ret);
		}
		redir = redir->next;
	}
	return (0);
}

int	read_heredocs(t_cmd *cmds, t_shell *shell)
{
	int	ret;

	while (cmds)
	{
		ret = hd_list(cmds->redirs, shell);
		if (ret != 0)
			return (ret);
		cmds = cmds->next;
	}
	return (0);
}
