/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 19:11:43 by ntassin           #+#    #+#             */
/*   Updated: 2026/08/25 19:20:10 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_path(char *to_split, char *command)
{
	char	**split_path;
	int		i;
	char	*joined_path;

	i = -1;
	split_path = ft_split(to_split, ':');
	while (split_path[++i] != NULL)
	{
		joined_path = ft_strjoin(split_path[i], command);
		if (access(joined_path, F_OK | X_OK) == 0)
			return (free_tab(split_path), joined_path);
		free(joined_path);
	}
	return (free_tab(split_path), NULL);
}

char	*get_path(char **envp, char *command)
{
	int		i;
	char	*str;

	i = 0;
	str = "PATH=";
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], str, 5) == 0)
			return (split_path(&envp[i][5], command));
		i++;
	}
	return (NULL);
}

void	set_path(char *arg, char **envp, t_cmd *cmds)
{
	char	*str;
	char	*find_path;

	cmds->path = NULL;
	if (cmds->args[0] == NULL)
		return ;
	if (access(arg, F_OK) == 0)
		cmds->path = ft_strdup(arg);
	else
	{
		str = ft_strjoin("/", cmds->args[0]);
		find_path = get_path(envp, str);
		if (find_path != NULL)
			cmds->path = find_path;
		free(str);
	}
}
