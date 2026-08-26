// #include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 150
#endif

void cmd_pwd(void)
{
	char	filename[BUFFER_SIZE];

	getcwd(filename, BUFFER_SIZE);
	printf("%s\n", filename);
}

int	main(void)
{
	cmd_pwd();
	return (0);
}