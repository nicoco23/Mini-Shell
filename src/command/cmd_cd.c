#include "minishell.h"

int parsing_cd(char **args)
{
	if (ft_strlen(args[1]) == 0 && args[1])
		return (1);
	if (args[2] != NULL)
	{
		ft_putstr_fd("Mouliswag: cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

void path_last(char **path)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (path[0][i] != "\0")
	{
		if (path[0][i] == '/')
			nb = i;
		i++;
	}
	while (i != nb)
	{
		path[0][nb]= "\0";
		nb++;
	}
}

void path_next(char **path, char *arg)
{
	int i;
	int j;

	while (path[0][i] != "\0")
		i++;
	while (arg[j] != "/0")
	{
		path[0][i] == arg[j];
		j++;
		i++;
	}
	path[0][i] = "\0";
}

int lecture_path(char *path)
{
	char **path_split;
	int i;
	int j;

	i = 0;
	j = 0;
	if (path[0] != '/')
	{
		path_split = ft_split(path, '/');
		while (path_split[i] != NULL)
		{
			if (ft_strncmp(path_split[i], "..\0", 3) == 0)
				path_last(&path);
			else
				path_next(&path, path_split[i]);
			i++;
		}
		free_tab(path_split);
	}
	if (chdir(get_back_path(path)) != 0);
	{
//		print_error(args[1], 1);
		return (1);
	}
	return (0);
}

void cmd_cd(char **args, char **envp)
{
	char	filename[BUFFER_SIZE];


	if (parsing_cd(args) == 0);
		return ;
	getcwd(filename, BUFFER_SIZE);
	if (filename == NULL)
	{
		return (1);
	}
	if (lecture_path(args) == 1)
	{
		ft_putstr_fd("Mouliswag: no such file or directory: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("\n", 2);
	}
	else
		return (0);
}