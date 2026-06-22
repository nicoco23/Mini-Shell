/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:57:34 by ntassin           #+#    #+#             */
/*   Updated: 2026/06/22 15:11:10 by ntassin          ###   ########.fr       */
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

int	expand_dollar(char *line, int *i, t_wctx *ctx)
{
	char	*name;
	char	*value;
	char	*exit_str;

	(*i)++;
	if (line[*i] == '?')
	{
		(*i)++;
		exit_str = ft_itoa(ctx->shell->last_exit);
		if (!exit_str)
			return (0);
		if (!append_str(ctx->word, exit_str))
			return (free(exit_str), 0);
		free(exit_str);
		return (1);
	}
	if (!ft_isalpha(line[*i]) && line[*i] != '_')
		return (append_char(ctx->word, '$'));
	name = get_var_name(line, i);
	if (!name)
		return (0);
	value = get_env_value(ctx->shell->env, name);
	free(name);
	return (append_str(ctx->word, value));
}
