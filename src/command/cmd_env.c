#include "minishell.h"

int cmd_env(char **env)
{
    int i;

    i = 0;
    if (env != NULL)
    {
        while (env[i] != NULL)
            printf("%s\n", env[i++]);
        return (0);
    }
    return (1);
}