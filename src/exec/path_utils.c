/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 19:11:43 by ntassin           #+#    #+#             */
/*   Updated: 2026/09/09 22:19:23 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*try_dir(char *dir, size_t len, char *command)
{
	char	*prefix;
	char	*joined;

	if (len == 0)
		prefix = ft_strdup(".");
	else
		prefix = ft_substr(dir, 0, len);
	if (!prefix)
		return (NULL);
	joined = ft_strjoin(prefix, command);
	free(prefix);
	if (joined && access(joined, F_OK | X_OK) == 0)
		return (joined);
	return (free(joined), NULL);
}

char	*split_path(char *to_split, char *command)
{
	char	*sep;
	char	*found;

	if (!to_split)
		return (NULL);
	while (1)
	{
		sep = ft_strchr(to_split, ':');
		if (sep)
			found = try_dir(to_split, sep - to_split, command);
		else
			found = try_dir(to_split, ft_strlen(to_split), command);
		if (found)
			return (found);
		if (!sep)
			return (NULL);
		to_split = sep + 1;
	}
}

char	*get_path(t_env *env, char *command)
{
	char	*path;

	path = env_get(env, "PATH");
	if (!path)
		return (NULL);
	return (split_path(path, command));
}

void	set_path(char *arg, t_env *env, t_cmd *cmds)
{
	char	*str;
	char	*find_path;

	cmds->path = NULL;
	if (cmds->args[0] == NULL || cmds->args[0][0] == '\0')
		return ;
	if (ft_strchr(arg, '/'))
	{
		if (access(arg, F_OK) == 0)
			cmds->path = ft_strdup(arg);
	}
	else
	{
		str = ft_strjoin("/", cmds->args[0]);
		find_path = get_path(env, str);
		if (find_path != NULL)
			cmds->path = find_path;
		free(str);
	}
}
