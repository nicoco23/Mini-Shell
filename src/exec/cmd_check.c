#include "minishell.h"

int check_cmd(t_cmd *cmds, char **env)
{
	if (ft_strncmp (cmds->args[0], "cd\0", 3) == 0)
		return (cmd_cd(cmds), 0);
	if (ft_strncmp (cmds->args[0], "pwd\0", 4) == 0)
		return (cmd_pwd(), 0);
	if (ft_strncmp(cmds->args[0], "echo\0", 5) == 0)
		return (cmd_echo(cmds->args), 0);
	if (ft_strncmp(cmds->args[0], "env\0", 4) == 0)
		return (cmd_env(env), 0);
	else
		return (1);
}
