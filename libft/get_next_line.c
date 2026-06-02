/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:49:28 by ltournie          #+#    #+#             */
/*   Updated: 2026/05/07 17:13:46 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_oneline(char	*str)
{
	char	*line;
	int		len;
	int		i;

	i = 0;
	if (ft_strchr(str, '\n') == NULL)
		len = (ft_strlen(str));
	else
		len = (line_len(str));
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*delete_line(char *str)
{
	char	*str_left;
	int		len;
	int		i;

	i = 0;
	if (ft_strchr(str, '\n') == NULL)
		len = (ft_strlen(str));
	else
		len = (line_len(str));
	str_left = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	while (str[len + i] != '\0')
	{
		str_left[i] = str[len + i];
		i++;
	}
	str_left[i] = '\0';
	free(str);
	return (str_left);
}

char	*join_lines(char *line1, char *line2)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * (ft_strlen(line1) + ft_strlen(line2) + 1));
	if (!new_line)
		return (NULL);
	while (line1[i] != '\0')
	{
		new_line[i] = line1[i];
		i++;
	}
	while (line2[j] != '\0')
	{
		new_line[i + j] = line2[j];
		j++;
	}
	new_line[i + j] = '\0';
	free(line1);
	return (new_line);
}

char	*readloop(int fd, char *str_read, char *line_stack, char *left_line)
{
	int	len;

	while (ft_strchr(line_stack, '\n') == NULL)
	{
		len = read(fd, str_read, BUFFER_SIZE);
		if (len <= 0)
		{
			if (ft_strlen(line_stack) > 0 && len == 0)
				break ;
			copy_str(left_line, "\0");
			free(str_read);
			free(line_stack);
			return (NULL);
		}
		str_read[len] = '\0';
		line_stack = join_lines(line_stack, str_read);
	}
	return (line_stack);
}

char	*get_next_line(int fd)
{
	static char	left_line[FD_MAX][BUFFER_SIZE + 1];
	char		*line_stack;
	char		*line;
	char		*str_read;

	if (fd < 0 || BUFFER_SIZE >= SIZE_MAX || BUFFER_SIZE <= 0 || fd > FD_MAX)
		return (NULL);
	str_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str_read)
		return (NULL);
	line_stack = malloc(sizeof(char)
			* (ft_strlen((const char *)left_line[fd]) + 1));
	if (!line_stack)
		return (free(str_read), NULL);
	copy_str(line_stack, left_line[fd]);
	line_stack = readloop(fd, str_read, line_stack, left_line[fd]);
	if (line_stack == NULL)
		return (NULL);
	line = get_oneline(line_stack);
	line_stack = delete_line(line_stack);
	copy_str(left_line[fd], line_stack);
	free(line_stack);
	free(str_read);
	return (line);
}
