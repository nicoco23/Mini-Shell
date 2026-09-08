/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:50:35 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/08 13:50:36 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_id(const char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_one(t_env *node)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(node->name, 1);
	if (node->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(node->value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

static int	print_export(t_env *lst)
{
	t_env	**sorted;
	int		i;
	int		n;

	sorted = sort_env_copy(lst, &n);
	if (!sorted)
		return (1);
	i = 0;
	while (i < n)
	{
		if (sorted[i]->visibility)
			print_one(sorted[i]);
		i++;
	}
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
	return (env_put_entry(&shell->env, arg, 1));
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
