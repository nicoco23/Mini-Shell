/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 10:37:11 by ntassin           #+#    #+#             */
/*   Updated: 2026/09/09 22:12:29 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	consume_char(char *line, int *i, t_wctx *ctx)
{
	if (line[*i] == '\'' || line[*i] == '"')
		return (read_quoted(line, i, line[*i], ctx));
	if (ctx->raw)
		return (append_char(ctx->word, line[(*i)++]));
	if (line[*i] == '$' && (line[*i + 1] == '\'' || line[*i + 1] == '"'))
		return ((*i)++, 1);
	if (line[*i] == '$')
		return (expand_dollar(line, i, ctx));
	return (append_char(ctx->word, line[(*i)++]));
}

static int	get_word(char *line, int *i, t_wctx *ctx)
{
	ctx->buf = ft_strdup("");
	if (!ctx->buf)
		return (0);
	ctx->word = &ctx->buf;
	*ctx->quoted = 0;
	while (line[*i] && !is_separator(line[*i]))
		if (!consume_char(line, i, ctx))
			return (free(ctx->buf), ctx->buf = NULL, 0);
	return (1);
}

static int	handle_operator(char *line, int *i, t_token **list, t_wctx *ctx)
{
	t_token	*token;

	if (line[*i] == '|')
		token = new_token(TOKEN_PIPE, "|");
	else if (line[*i] == '<' && line[*i + 1] == '<')
		token = new_token(TOKEN_REDIR_HEREDOC, "<<");
	else if (line[*i] == '<')
		token = new_token(TOKEN_REDIR_IN, "<");
	else if (line[*i] == '>' && line[*i + 1] == '>')
		token = new_token(TOKEN_REDIR_APPEND, ">>");
	else
		token = new_token(TOKEN_REDIR_OUT, ">");
	if (!token)
		return (0);
	*i += ft_strlen(token->value);
	ctx->raw = (token->type == TOKEN_REDIR_HEREDOC);
	return (token_add_back(list, token), 1);
}

static int	handle_word(char *line, int *i, t_token **list, t_wctx *ctx)
{
	t_token	*token;
	char	*word;

	if (!get_word(line, i, ctx))
		return (ctx->raw = 0, 0);
	ctx->raw = 0;
	word = ctx->buf;
	if (word[0] == '\0' && !*ctx->quoted)
		return (free(word), 1);
	token = new_token(TOKEN_WORD, word);
	free(word);
	if (!token)
		return (0);
	token->quoted = *ctx->quoted;
	return (token_add_back(list, token), 1);
}

t_token	*lexer(char *line, t_shell *shell, int *err)
{
	t_token	*list;
	t_wctx	ctx;
	int		quoted;
	int		i;

	list = NULL;
	i = 0;
	*err = 0;
	quoted = 0;
	ctx.shell = shell;
	ctx.quoted = &quoted;
	ctx.raw = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			if (!handle_operator(line, &i, &list, &ctx))
				return (*err = 1, free_tokens(list), NULL);
		}
		else if (!handle_word(line, &i, &list, &ctx))
			return (*err = 1, free_tokens(list), NULL);
	}
	return (list);
}
