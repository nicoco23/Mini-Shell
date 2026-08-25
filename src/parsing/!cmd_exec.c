#include "minishell.h"


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
	// write(2, ": ", 2);
	if (i == 0)
		ft_putstr_fd("command not found\n", 2);
	else
		perror(str);
}

char	*split_path(char *to_split, char *command)
{
	char	**split_path;
	int		i;
	char	*joined_path;

	i = -1;
	split_path = ft_split(to_split, ':');
	while (split_path[++i] != NULL)
	{
		joined_path = ft_strjoin(split_path[i], command);
		if (access(joined_path, F_OK | X_OK) == 0)
			return (free_tab(split_path), joined_path);
		free(joined_path);
	}
	free_tab(split_path);
	return (NULL);
}

char	*get_path(char **envp, char *command)
{
	int		i;
	char	*str;

	i = 0;
	str = "PATH=";
	while (envp[i] != NULL)
	{
		if (envp[i][0] != 'P')
			i++;
		else if (ft_strncmp(envp[i], str, 5) == 0)
			return (split_path(&envp[i][5], command));
		else
			i++;
	}
	return (NULL);
}

void	set_path(char *arg, char **envp, t_cmd *cmds)
{
	char	*str;
	char	*find_path;

	cmds->path = NULL;
	if (cmds->args[0] == NULL)
		return ;
	if (access(arg, F_OK) == 0) // si le file envoyer == path
		cmds->path = strdup(arg);
	else
	{
		str = ft_strjoin("/\0", cmds->args[0]);
		find_path = get_path(envp, str);
		if (find_path != NULL)
			cmds->path = find_path;
		free(str);
	}
}

// static void	check_exec(t_cmd *cmds, int fd)
// {
// 	if (fd < 0)
// 	{
// 		if (ft_strlen(cmds->argv[4]) == 0)
// 			print_error(cmds->exec[0], &(cmds->argv[0][2]));
// 		else
// 			print_error(cmds->argv[4], &(cmds->argv[0][2]));
// 		if (cmds->path != NULL)
// 			(free_struct(cmds), exit(1));
// 		else
// 			(free_tab(cmds->exec), exit(1));
// 	}
// 	if (cmds->path == NULL || cmds->exec[0] == NULL)
// 	{
// 		print_error_not_found(cmds->argv[3], &(cmds->argv[0][2]));
// 		(free_tab(cmds->exec), exit(127));
// 	}
// 	if (access(cmds->path, F_OK) < 0)
// 	{
// 		print_error(cmds->argv[3], &(cmds->argv[0][2]));
// 		(free_tab(cmds->exec), exit(1));
// 	}
// }

void pipe_in(t_cmd *cmds, char **envp, int i)
{
	int fd;

	close(cmds->redirs->fd_pipe[0]);
	fd = open(cmds->redirs->target, O_RDONLY);
	// check_exec(cmds, fd);
	(dup2(fd, STDIN_FILENO), close(fd));
	(dup2(cmds->redirs->fd_pipe[1], STDOUT_FILENO), close(cmds->redirs->fd_pipe[1]));
	cmds->exit_status[i] = execve(cmds->path, cmds->args, envp);
	print_error(cmds->args[0], 1);
	(free_struct(cmds), exit(127));
}

void pipe_mid(t_cmd *cmds, char **envp, int i)
{
	// check_exec(cmds, fd);
	(dup2(cmds->redirs->fd_pipe[0], STDIN_FILENO), close(cmds->redirs->fd_pipe[0]));
	(dup2(cmds->redirs->fd_pipe[1], STDOUT_FILENO), close(cmds->redirs->fd_pipe[1]));
	cmds->exit_status[i] = execve(cmds->path, cmds->args, envp);
	print_error(cmds->args[0], 1);
	(free_struct(cmds), exit(127));
}

void pipe_out(t_cmd *cmds, char **envp, int i)
{
	int fd;

	close(cmds->redirs->fd_pipe[1]);
	fd = open(cmds->redirs->target, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	// check_exec(cmds, fd);
	(dup2(cmds->redirs->fd_pipe[0], STDIN_FILENO), close(cmds->redirs->fd_pipe[0]));
	(dup2(fd, STDOUT_FILENO), close(fd));
	cmds->exit_status[i] = execve(cmds->path, cmds->args, envp);
	print_error(cmds->args[0], 1);
	(free_struct(cmds), exit(127));
}

void	redirs_exec(t_cmd *cmds, char **envp, t_token_type token, int i)
{
	if (token == TOKEN_PIPE_IN)
		pipe_in(cmds, envp, i);
	else if (token == TOKEN_PIPE_MID)
		pipe_mid(cmds, envp, i);
	else if (token == TOKEN_PIPE_OUT)
		pipe_out(cmds, envp, i);
	else
	{
	cmds->exit_status[i] = execve(cmds->path, cmds->args, envp);
	print_error(cmds->args[0], 1);
	(free_struct(cmds), exit(127));
	}
}

void	exec(t_shell *shell)
{
	int		*pid;
	int		lst_size;
	int		i;

//	if (argc != 5 || ft_strlen(argv[2]) == 0 || ft_strlen(argv[3]) == 0)
//		return (1);
	lst_size = ft_lstsize(shell->cmds);
	i = 0;
	pid = malloc(sizeof(int) * lst_size);
	shell->cmds->exit_status = malloc(sizeof(int) * lst_size);
	set_path(shell->cmds->args[0], shell->env, shell->cmds);
	if (pipe(shell->cmds->redirs->fd_pipe) == -1)
		return (1);
	pid[i] = fork();
	if (pid[i] == 0)
		redirs_exec(shell->cmds, shell->env, TOKEN_PIPE_IN, i);
	i++;
	while (shell->cmds->next != NULL && lst_size != i)
	{
		shell->cmds = shell->cmds->next;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if ((lst_size - 1) ==  i)
				redirs_exec(shell->cmds, shell->env, TOKEN_PIPE_OUT, i);
			else
				redirs_exec(shell->cmds, shell->env, TOKEN_PIPE_MID, i);
		}
		i++;
	}
	close(shell->cmds->redirs->fd_pipe[0]);
	close(shell->cmds->redirs->fd_pipe[1]);
	i = 0;
	while (i != lst_size - 1)
	{
		if (waitpid(pid, &shell->cmds->exit_status[i], 0) == -1)
		{
			perror("Commands not found\n");
			g_signal = ((shell->cmds->exit_status[i] >> 8) & 0xFF);
			free_struct(shell);
		}
	}
}
