// #include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2147483647
#endif

int cmd_pwd(void)
{
	char	filename[i * BUFFER_SIZE];

	getcwd(filename, BUFFER_SIZE);
	if (filename != NULL)
	{
		printf("%s\n", filename);
		return (0);
	}
	else if (i *)
		cmd_
}

int	main(void)
{
	cmd_pwd();
	return (0);
}