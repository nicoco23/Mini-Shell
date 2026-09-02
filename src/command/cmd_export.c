#include "minishell.h"

int	is_valid_id(const char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

static void	print_one(char *entry)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (entry[i] && entry[i] != '=')
		ft_putchar_fd(entry[i++], 1);
	if (entry[i] == '=')
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(entry + i + 1, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

static int	print_export(char **env)
{
	char	**sorted;
	int		i;
	int		n;

	sorted = sort_env_copy(env, &n);
	if (!sorted)
		return (1);
	i = 0;
	while (i < n)
		print_one(sorted[i++]);
	free(sorted);
	return (0);
}

static int	export_one(t_shell *shell, char *arg)
{
	if (!is_valid_id(arg))
	{
		ft_putstr_fd("mouliswag: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (ft_strchr(arg, '='))
		return (env_set(shell, arg));
	return (0);
}

int	cmd_export(t_shell *shell, char **args)
{
	int	status;
	int	i;

	if (!args[1])
		return (print_export(shell->env));
	status = 0;
	i = 0;
	while (args[++i])
		if (export_one(shell, args[i]))
			status = 1;
	return (status);
}
