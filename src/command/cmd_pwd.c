#include "minishell.h"

int	cmd_pwd(void)
{
	char	filename[BUFFER_SIZE];

	if (getcwd(filename, BUFFER_SIZE) == NULL)
		return (1);
	else
	{
		ft_putstr_fd(filename, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
}
