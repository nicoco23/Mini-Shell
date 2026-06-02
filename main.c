/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 08:50:43 by codespace         #+#    #+#             */
/*   Updated: 2026/06/02 15:02:51 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	printf("Welcome to Minishell!\n");
	while(1)
	{
		printf("placeholder$");
		parsing();
	}
	return (0);
}
