/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 10:37:11 by ntassin           #+#    #+#             */
/*   Updated: 2026/08/20 15:49:59 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	consume_char(char *line, int *i, t_wctx *ctx)
{
	if (line[*i] == '\'' || line[*i] == '"')
	{
		if (!read_quoted(line, i, line[*i], ctx))
			return (0);
	}
	else if (line[*i] == '$')
	{
		if (!expand_dollar(line, i, ctx))
			return (0);
	}
	else if (!append_char(ctx->word, line[(*i)++]))
		return (0);
	return (1);
}

char	*get_word(char *line, int *i, t_shell *shell, int *quoted)
{
	char	*word;
	t_wctx	ctx;

	word = ft_strdup("");
	if (!word)
		return (NULL);
	ctx.word = &word;
	ctx.shell = shell;
	ctx.quoted = quoted;
	*quoted = 0;
	while (line[*i] && !is_separator(line[*i]))
		if (!consume_char(line, i, &ctx))
			return (free(word), NULL);
	return (word);
}

t_token	*get_operator(char *line, int *i)
{
	if (line[*i] == '|')
		return (((*i)++), new_token(TOKEN_PIPE, "|"));
	if (line[*i] == '<' && line[*i + 1] == '<')
		return ((*i) += 2, new_token(TOKEN_REDIR_HEREDOC, "<<"));
	if (line[*i] == '<')
		return (((*i)++), new_token(TOKEN_REDIR_IN, "<"));
	if (line[*i] == '>' && line[*i + 1] == '>')
		return ((*i) += 2, new_token(TOKEN_REDIR_APPEND, ">>"));
	(*i)++;
	return (new_token(TOKEN_REDIR_OUT, ">"));
}

static int	handle_word(char *line, int *i, t_token **list, t_shell *shell)
{
	t_token	*token;
	char	*word;
	int		quoted;

	word = get_word(line, i, shell, &quoted);
	if (!word)
		return (0);
	token = new_token(TOKEN_WORD, word);
	free(word);
	if (!token)
		return (0);
	token->quoted = quoted;
	token_add_back(list, token);
	return (1);
}

t_token	*lexer(char *line, t_shell *shell)
{
	t_token	*list;
	t_token	*token;
	int		i;

	list = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			token = get_operator(line, &i);
			if (!token)
				return (free_tokens(list), NULL);
			token_add_back(&list, token);
		}
		else if (!handle_word(line, &i, &list, shell))
			return (free_tokens(list), NULL);
	}
	return (list);
}
