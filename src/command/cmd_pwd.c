#include "minishell.h"

int	cmd_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (cwd_error("pwd"), 1);
	if (putendl_check(cwd, 1))
		return (write_error("pwd"), 1);
	return (0);
}
