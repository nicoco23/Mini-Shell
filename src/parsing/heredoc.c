#include "minishell.h"

static char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*out;
	t_wctx	ctx;
	int		quoted;
	int		i;

	out = ft_strdup("");
	if (!out)
		return (NULL);
	quoted = 0;
	ctx.word = &out;
	ctx.shell = shell;
	ctx.quoted = &quoted;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (!expand_dollar(line, &i, &ctx))
				return (free(out), NULL);
		}
		else if (!append_char(&out, line[i++]))
			return (NULL);
	}
	return (out);
}

static int	write_heredoc_line(t_shell *shell, t_redir *rd, int fd, char *line)
{
	char	*expanded;

	if (rd->quoted)
		return (ft_putendl_fd(line, fd), 0);
	expanded = expand_heredoc_line(line, shell);
	if (!expanded)
		return (1);
	ft_putendl_fd(expanded, fd);
	return (free(expanded), 0);
}

static int	heredoc_loop(t_shell *shell, t_redir *rd, int fd)
{
	char	*line;
	int		saved;

	saved = dup(STDIN_FILENO);
	line = readline("> ");
	while (line && g_signal != SIGINT)
	{
		if (ft_strlen(line) == ft_strlen(rd->target)
			&& !ft_strncmp(line, rd->target, ft_strlen(rd->target)))
			return (free(line), close(saved), 0);
		if (write_heredoc_line(shell, rd, fd, line))
			return (free(line), close(saved), -1);
		free(line);
		line = readline("> ");
	}
	free(line);
	if (g_signal == SIGINT)
		dup2(saved, STDIN_FILENO);
	return (close(saved), -1);
}

static int	read_one_heredoc(t_shell *shell, t_redir *redir)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	if (heredoc_loop(shell, redir, pipe_fd[1]) == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	close(pipe_fd[1]);
	redir->fd_pipe[0] = pipe_fd[0];
	return (0);
}

int	read_heredocs(t_shell *shell)
{
	t_cmd	*cmds;
	t_redir	*redir;
	int		interrupted;

	interrupted = 0;
	cmds = shell->cmds;
	setup_signal_heredoc();
	while (cmds && !interrupted)
	{
		redir = cmds->redirs;
		while (redir && !interrupted)
		{
			if (redir->type == TOKEN_REDIR_HEREDOC
				&& read_one_heredoc(shell, redir) == -1)
				interrupted = 1;
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	setup_signal_prompt();
	g_signal = 0;
	return (interrupted);
}
