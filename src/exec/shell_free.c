#include "minishell.h"

void	shell_free(t_shell *shell)
{
	rl_clear_history();
	if (shell->cmds)
		free_cmds(shell->cmds);
	shell->cmds = NULL;
	if (shell->env)
		free_tab(shell->env);
	shell->env = NULL;
	free(shell->line);
	shell->line = NULL;
	free(shell->pids);
	shell->pids = NULL;
}

void	clean_exit(t_shell *shell, int code)
{
	shell_free(shell);
	exit(code);
}
