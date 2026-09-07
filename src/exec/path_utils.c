/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 19:11:43 by ntassin           #+#    #+#             */
/*   Updated: 2026/09/07 15:33:03 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_path(char *to_split, char *command)
{
	char	**split;
	char	*joined;
	int		i;

	split = ft_split(to_split, ':');
	if (!split)
		return (NULL);
	i = -1;
	while (split[++i])
	{
		joined = ft_strjoin(split[i], command);
		if (joined && access(joined, F_OK | X_OK) == 0)
			return (free_tab(split), joined);
		free(joined);
	}
	return (free_tab(split), NULL);
}

char	*get_path(char **envp, char *command)
{
	char	*path;

	path = get_env_value(envp, "PATH");
	if (!path)
		return (split_path(DEFAULT_PATH, command));
	if (!path[0])
		return (NULL);
	return (split_path(path, command));
}

void	set_path(char *arg, char **envp, t_cmd *cmds)
{
	char	*str;
	char	*find_path;

	cmds->path = NULL;
	if (cmds->args[0] == NULL)
		return ;
	if (ft_strchr(arg, '/'))
	{
		if (access(arg, F_OK) == 0)
			cmds->path = ft_strdup(arg);
	}
	else
	{
		str = ft_strjoin("/", cmds->args[0]);
		find_path = get_path(envp, str);
		if (find_path != NULL)
			cmds->path = find_path;
		free(str);
	}
}
