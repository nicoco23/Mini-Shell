/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 19:20:27 by ntassin           #+#    #+#             */
/*   Updated: 2026/08/26 10:18:37 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_listsize_cmd(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	free_tab(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
}

void	print_error(char *str, int i)
{
	ft_putstr_fd("mouliswag: ", 2);
	if (i == 0)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found...\n", 2);
	}
	else
		perror(str);
}

void	close_if_open(int fd)
{
	if (fd != -1)
		close(fd);
}

int	apply_redirs(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		fd = -1;
		if (r->type == TOKEN_REDIR_IN)
			fd = open(r->target, O_RDONLY);
		else if (r->type == TOKEN_REDIR_OUT)
			fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (r->type == TOKEN_REDIR_APPEND)
			fd = open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (r->type == TOKEN_REDIR_HEREDOC)
			fd = r->fd_pipe[0];
		if (fd == -1)
			return (ft_putstr_fd("mouliswag: ", 2), perror(r->target), 1);
		if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_REDIR_HEREDOC)
			(dup2(fd, STDIN_FILENO), close(fd), r->fd_pipe[0] = -1);
		else
			(dup2(fd, STDOUT_FILENO), close(fd));
		r = r->next;
	}
	return (0);
}
