#include "minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	str_to_ll(const char *s, long long *out)
{
	unsigned long long	acc;
	unsigned long long	limit;
	int					sign;
	int					i;

	acc = 0;
	sign = 1;
	i = 0;
	while (is_space(s[i]))
		i++;
	if ((s[i] == '+' || s[i] == '-') && s[i++] == '-')
		sign = -1;
	if (!ft_isdigit(s[i]))
		return (0);
	limit = (unsigned long long)LLONG_MAX + (sign < 0);
	while (ft_isdigit(s[i]))
	{
		if (acc > (limit - (s[i] - '0')) / 10)
			return (0);
		acc = acc * 10 + (s[i++] - '0');
	}
	while (is_space(s[i]))
		i++;
	return (s[i] == '\0' && (*out = (long long)acc * sign, 1));
}

static void	clean_exit(t_shell *shell, int code)
{
	rl_clear_history();
	if (shell->cmds)
		free_cmds(shell->cmds);
	if (shell->env)
		free_tab(shell->env);
	exit(code);
}

int	cmd_exit(t_shell *shell, char **args)
{
	long long	code;

	ft_putstr_fd("exit\n", 2);
	if (!args[1])
		clean_exit(shell, (unsigned char)shell->last_exit);
	if (!str_to_ll(args[1], &code))
	{
		ft_putstr_fd("mouliswag: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_exit(shell, 2);
	}
	if (args[2])
		return (ft_putstr_fd("mouliswag: exit: too many arguments\n", 2), 1);
	clean_exit(shell, (unsigned char)code);
	return (0);
}
