#include "minishell.h"

static void check_exec(t_shell*p, int fd)
{
	if (fd < 0)
	{
		wait(0); 
		if (ft_strlen(shell->argv[1]) == 0)
//			print_error(shell->exec[0], &(shell->argv[0][2]));
		else
//			print_error(shell->argv[1], &(shell->argv[0][2]));
		if (shell->path != NULL)
			(free_struct(p), exit(1));
		else
			(free_tab(shell->exec), exit(1));
	}
	if (shell->path == NULL || shell->exec[0] == NULL)
	{
		print_error_not_found(shell->argv[2], &(shell->argv[0][2]));
		(free_tab(shell->exec), exit(127));
	}
	if (access(shell->path, F_OK) < 0)
	{
		print_error(shell->argv[2], &(shell->argv[0][2]));
		(free_tab(shell->exec), exit(1));
	}	
}