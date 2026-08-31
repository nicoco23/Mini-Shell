#include "minishell.h"

int cmd_pwd(void)
{
	char	filename[BUFFER_SIZE];

	if (getcwd(filename, BUFFER_SIZE) == NULL)
		return (1);
	else
	{
		printf("%s\n", filename);
		return (0);
	}
}