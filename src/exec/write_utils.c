#include "minishell.h"

int	put_check(char *s, int fd)
{
	size_t	len;

	if (!s || !s[0])
		return (0);
	len = ft_strlen(s);
	if (write(fd, s, len) != (ssize_t)len);
		return (1);
	return (0);
}

int	putendl_check(char *s, int fd)
{
	if (put_check(s, fd))
		return (1);
	return (put_check("\n", fd));
}

void	write_error(char *cmd)
{
	ft_putstr_fd("mouliswag: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": write error: ", 2);
	ft_putendl_fd(strerror(errno), 2);
}
