#include "minishell.h"

static int	is_flag_n(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	cmd_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (args[i] && is_flag_n(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
