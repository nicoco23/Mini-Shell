#include "minishell.h"

int check_cmd(t_cmd *cmds)
{
	if (ft_strncmp (cmds->args[0], "cd\0", 3) == 0)
	{
		printf("in cd\n");
		return (cmd_cd(cmds), 0);
	}
	if (ft_strncmp (cmds->args[0], "pwd\0", 4) == 0)
		return (cmd_pwd(), 0);
	if (ft_strncmp(cmds->args[0], "echo\0", 5) == 0)
		return (cmd_echo(cmds->args), 0);
	else
		return (1);
}
