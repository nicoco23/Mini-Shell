#include "minishell.h"

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

void type_in(t_cmd *cmds, char **envp)
{
	int fd;

	close(cmds->fd_pipe[0]);
	fd = open(cmds->redirs->target, O_RDONLY);
	// check_exec(cmds, fd);
	(dup2(fd, STDIN_FILENO), close(fd));
	(dup2(cmds->redirs->fd_pipe[1], STDOUT_FILENO), close(cmds->fd_pipe[1]));
	cmds->exit_status = execve(cmds->path, cmds->args, envp);
	print_error(cmds->args[0], &(cmds->argv[0][2]));
	(free_struct(cmds), exit(127));
}

void type_mid(t_cmd *cmds, char **envp)
{
	// check_exec(cmds, fd);
	(dup2(cmds->redirs->fd_pipe[0], STDIN_FILENO), close(fd));
	(dup2(cmds->redirs->fd_pipe[0], STDOUT_FILENO), close(fd));
	cmds->exit_status = execve(cmds->path, cmds->args, envp);
	print_error(cmds->args[0], &(cmds->argv[0][2]));
	(free_struct(cmds), exit(127));
}

void type_out(t_cmd *cmds, char **envp)
{
	int fd;

	close(cmds->fd_pipe[1]);
	fd = open(cmds->redirs->target, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	// check_exec(cmds, fd);
	(dup2(cmds->fd_pipe[0], STDIN_FILENO), close(cmds->fd_pipe[0]));
	(dup2(fd, STDOUT_FILENO), close(fd));
	cmds->exit_status = execve(cmds->path, cmds->args, envp);
	print_error(cmds->args[0], &(cmds->argv[0][2]));
	(free_struct(cmds), exit(127));
}

void	exec(t_cmd *cmds, char **envp)
{
	int	fd;

	set_path(cmds->args[0], envp, cmds);
	//fonction checkpipe pour savoir si la pipe est une entree/sortie/pipe to pipe pour set les fd
	if (cmds->redirs->type == TOKEN_PIPE_IN)
		type_in(cmds, envp);
	else if (cmds->redirs->type == TOKEN_PIPE_MID)
		type_mid(cmds, envp);
	else if (cmds->redirs->type == TOKEN_PIPE_OUT)
		type_out(cmds, envp);
	else
	{
	cmds->exit_status = execve(cmds->path, cmds->args, envp);
	print_error(cmds->args[0], &(cmds->argv[0][2]));
	(free_struct(cmds), exit(127));
	}
}