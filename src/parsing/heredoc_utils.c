/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 14:26:19 by ntassin           #+#    #+#             */
/*   Updated: 2026/09/09 14:26:42 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hd_eof_warning(char *delim)
{
	ft_putstr_fd("mouliswag: warning: here-document delimited "
		"by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static int	hd_consume(char *line, int *i, t_wctx *ctx)
{
	if (line[*i] == '$')
		return (expand_dollar(line, i, ctx));
	return (append_char(ctx->word, line[(*i)++]));
}

static char	*expand_hd_line(char *line, t_shell *shell)
{
	char	*out;
	t_wctx	ctx;
	int		quoted;
	int		i;

	out = ft_strdup("");
	if (!out)
		return (NULL);
	quoted = 0;
	i = 0;
	ctx.word = &out;
	ctx.shell = shell;
	ctx.quoted = &quoted;
	ctx.raw = 0;
	while (line[i])
		if (!hd_consume(line, &i, &ctx))
			return (NULL);
	return (out);
}

static int	write_hd_line(int fd, char *line, int quoted, t_shell *shell)
{
	char	*exp;

	if (quoted)
		return (ft_putendl_fd(line, fd), 1);
	exp = expand_hd_line(line, shell);
	if (!exp)
		return (0);
	ft_putendl_fd(exp, fd);
	return (free(exp), 1);
}

int	heredoc_loop(int fd, t_redir *redir, t_shell *shell)
{
	char	*line;
	int		saved;

	saved = dup(STDIN_FILENO);
	line = read_input_line("> ");
	while (line && g_signal != SIGINT)
	{
		if (!ft_strncmp(line, redir->target, ft_strlen(redir->target) + 1))
			return (free(line), close(saved), 0);
		if (!write_hd_line(fd, line, redir->quoted, shell))
			return (free(line), close(saved), -2);
		free(line);
		line = read_input_line("> ");
	}
	free(line);
	if (g_signal == SIGINT)
		return (dup2(saved, STDIN_FILENO), close(saved), -1);
	close(saved);
	return (hd_eof_warning(redir->target), 0);
}
