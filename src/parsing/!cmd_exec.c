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

void	set_path(char *arg, char **envp, t_pipex *p)
{
	char	*str;
	char	*find_path;

	p->path = NULL;
	if (p->exec[0] == NULL)
		return ;
	if (access(arg, F_OK) == 0)
		p->path = strdup(arg);
	else
	{
		str = ft_strjoin("/\0", p->exec[0]);
		find_path = get_path(envp, str);
		if (find_path != NULL)
		{
			p->path = find_path;
			free(str);
			if (p->path != NULL)
				return ;
		}
		free(str);
	}
}

static void	check_exec2(t_shell *p, int fd)
{
	if (fd < 0)
	{
		if (ft_strlen(p->argv[4]) == 0)
			print_error(p->exec[0], &(p->argv[0][2]));
		else
			print_error(p->argv[4], &(p->argv[0][2]));
		if (p->path != NULL)
			(free_struct(p), exit(1));
		else
			(free_tab(p->exec), exit(1));
	}
	if (p->path == NULL || p->exec[0] == NULL)
	{
		print_error_not_found(p->argv[3], &(p->argv[0][2]));
		(free_tab(p->exec), exit(127));
	}
	if (access(p->path, F_OK) < 0)
	{
		print_error(p->argv[3], &(p->argv[0][2]));
		(free_tab(p->exec), exit(1));
	}
}

void	exec1(t_shell *p)
{
	int	fd;

	close(p->fd_pipe[0]);
	fd = open(p->argv[1], O_RDONLY);
	check_exec1(p, fd);
	(dup2(fd, STDIN_FILENO), close(fd));
	(dup2(p->fd_pipe[1], STDOUT_FILENO), close(p->fd_pipe[1]));
	p->exit_status1 = execve(p->path, p->exec, p->envp);
	print_error(p->argv[2], &(p->argv[0][2]));
	(free_struct(p), exit(127));
}

void	exec2(t_shell *p)
{
	int	fd;

	close(p->fd_pipe[1]);
	fd = open(p->argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	check_exec2(p, fd);
	(dup2(p->fd_pipe[0], STDIN_FILENO), close(p->fd_pipe[0]));
	(dup2(fd, STDOUT_FILENO), close(fd));
	execve(p->path, p->exec, p->envp);
	print_error(p->argv[3], &(p->argv[0][2]));
	(free_struct(p), exit(127));
}