/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:57:34 by ntassin           #+#    #+#             */
/*   Updated: 2026/09/02 17:23:37 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **env, char *name)
{
	int	i;
	int	len;

	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	append_str(char **word, char *str)
{
	char	*tmp;

	if (!str)
		return (1);
	tmp = ft_strjoin(*word, str);
	free(*word);
	*word = tmp;
	return (tmp != NULL);
}

static char	*get_var_name(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	return (ft_substr(line, start, *i - start));
}

static int	expand_exit(t_wctx *ctx)
{
	char	*exit_str;
	int		ok;

	exit_str = ft_itoa(ctx->shell->last_exit);
	if (!exit_str)
		return (0);
	ok = append_str(ctx->word, exit_str);
	free(exit_str);
	return (ok);
}

int	expand_dollar(char *line, int *i, t_wctx *ctx)
{
	char	*name;
	char	*value;

	(*i)++;
	if (line[*i] == '?')
		return ((*i)++, expand_exit(ctx));
	if (ft_isdigit(line[*i]))
		return ((*i)++, 1);
	if (!ft_isalpha(line[*i]) && line[*i] != '_')
		return (append_char(ctx->word, '$'));
	name = get_var_name(line, i);
	if (!name)
		return (0);
	value = get_env_value(ctx->shell->env, name);
	free(name);
	return (append_str(ctx->word, value));
}
