/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:01:38 by ntassin           #+#    #+#             */
/*   Updated: 2026/08/17 18:36:13 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	syntax_error(char *token_value)
{
	ft_printf("mouliswag: syntax error near unexpected token `%s'\n",
		token_value);
}

static int	check_pipes(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == TOKEN_PIPE)
		return (syntax_error("|"), 0);
	while (tokens->next)
	{
		if (tokens->type == TOKEN_PIPE && tokens->next->type == TOKEN_PIPE)
			return (syntax_error("|"), 0);
		tokens = tokens->next;
	}
	if (tokens->type == TOKEN_PIPE)
		return (syntax_error("newline"), 0);
	return (1);
}

static int	check_redirs(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_REDIR_IN || tokens->type == TOKEN_REDIR_OUT
			|| tokens->type == TOKEN_REDIR_APPEND
			|| tokens->type == TOKEN_REDIR_HEREDOC)
		{
			if (!tokens->next)
				return (syntax_error("newline"), 0);
			if (tokens->next->type != TOKEN_WORD)
				return (syntax_error(tokens->next->value), 0);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	check_syntax(t_token *tokens)
{
	if (!check_pipes(tokens))
		return (0);
	if (!check_redirs(tokens))
		return (0);
	return (1);
}
