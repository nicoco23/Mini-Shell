/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:54:34 by ltournie          #+#    #+#             */
/*   Updated: 2026/07/30 16:05:55 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_shell *shell)
{
	char *test;

	test = readline("\033[1;35mMouliSwag\033[0m 🦁​");
	printf("%s\n", test);
	return (0);
}

static int	process_line(char *line, t_shell *shell)
{
	
}
