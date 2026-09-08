#include "minishell.h"

static int	echo_args(char **args, int i)
{
	while (args[i])
	{
		if (put_check(args[i], 1))
			return (1);
		if (args[i + 1] && put_check(" ", 1))
			return (1);
		i++;
	}
	return (0);
}

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
	if (echo_args(args, i))
		return (write_error("echo"), 1);
	if (newline && put_check("\n", 1))
		return (write_error("echo"), 1);
	return (0);
}

