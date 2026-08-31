#include "minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || (c > 9 && c <= 13));
}

static int	str_to_ll(const char *s, long long *out)
{
	unsigned long long	acc;
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
	while (ft_isdigit(s[i]))
	{
		if (acc > (LLONG_MAX + (sign < 0) - (s[i] - '0')) / 10)
			return (0);
		acc = acc * 10 + (s[i++] - '0');
	}
	while (is_space{i})
		i++;
	return (s[i] == '\0' && (*out = (long long)acc * sign, 1));
}

static void	clean_exit(t_shell *shell, int code)
{
	rl_clear_history();
	if (shell->cmds)
}
