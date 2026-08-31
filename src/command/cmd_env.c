#include "minishell.h"

int cmd_env(char **env)
{
    int i;

    i = 0;
    if (env != NULL)
    {
        while (env[i] != NULL)
        {
            ft_putstr_fd(env[i++], 1);
            ft_putstr_fd("\n", 1);
        }
        return (0);
    }
    return (1);
}