#include "minishell.h"

int	cmd_env(t_env *env)
{
	while (env)
	{
		if (env->visibility && env->value)
		{
			if (put_check(env->name, 1) || put_check("=", 1)
				|| putendl_check(env->value, 1))
				return (write_error("env"), 1);
		}
		env = env->next;
	}
	return (0);
}
