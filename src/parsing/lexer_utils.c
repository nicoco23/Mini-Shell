/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 10:37:27 by ntassin           #+#    #+#             */
/*   Updated: 2026/08/20 10:31:27 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
		return (free(token), NULL);
	return (token);
}

void	token_add_back(t_token **list, t_token *new)
{
	t_token	*last;

	if (!*list)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
}

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '|'
		|| c == '<' || c == '>');
}

int	append_char(char **word, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(*word, buf);
	free(*word);
	*word = tmp;
	return (tmp != NULL);
}

int	read_quoted(char *line, int *i, char quote, t_wctx *ctx)
{
	*ctx->quoted = 1;
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		if (quote == '"' && line[*i] == '$')
		{
			if (!expand_dollar(line, i, ctx))
				return (0);
		}
		else if (!append_char(ctx->word, line[(*i)++]))
			return (0);
	}
	if (!line[*i])
	{
		ft_printf("mouliswag: unclosed quote\n");
		return (0);
	}
	(*i)++;
	return (1);
}
