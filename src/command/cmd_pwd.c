#include "minishell.h"

int cmd_pwd(void)
{
	char	filename[BUFFER_SIZE];

	getcwd(filename, BUFFER_SIZE);
	if (filename != NULL)
	{
		printf("%s\n", filename);
		return (0);
	}
	else
		return(1);
}