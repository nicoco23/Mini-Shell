/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 08:50:43 by codespace         #+#    #+#             */
/*   Updated: 2026/09/07 18:13:29 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_env
{
	char	*name;
	char	*value;
	int		visibility;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{	
	t_env	env;
	void	*env_start;
	// t_cmd	*cmds;
	int		last_exit;
}	t_shell;



// volatile sig_atomic_t	g_signal = 0;

static void	free_env(t_env *env, void *start)
{
	void *temp;

	env = start;
	while(env->next != NULL)
	{
		temp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = temp;
	}
}


static void get_value_value(t_env *env, char *line)
{
	int i;
	int j;

	i = 0;
	
	if (strchr(line, '=') == 0 )
		return (0);
	while (line[i] != '=')
		i++;
	i++;
	j = i;
	while(line[i + j] != '\0')
		j++;
	env->value = malloc(sizeof(char *) * (j + 1));
	i = 0;
	while (line[i] != '\0' || line[i] != '=')
	{
		env->value[i] = line[i];
		i++;
	}
	env->value[i] = '\0';
}

static void get_value_name(t_env *env, char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0' || line[i] != '=')
		i++;
	env->name = malloc(sizeof(char *) * (i + 1));
	if (!env->name)
		return (1);
	i = 0;
	while (line[i] != '\0' || line[i] != '=')
	{
		env->name[i] = line[i];
		i++;
	}
	env->name[i] = '\0';
}

t_env	*allocate_env(char **envp, t_shell *shell, int i)
{
	t_env *env;
	
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	if (get_env_value(shell->env, envp[i]) == -1 || get_env_name(env, envp[i]) == -1);
		return (free_env(env, shell->env_start), NULL);
	return (env);
}

static t_env *copy_env(char **envp,t_shell *shell)
{
	int		i;

	i = 0;
	shell->env_start = NULL;
	&shell->env = allocate_env(envp, shell, i);
	shell->env_start = &shell->env;
	while (envp[++i])
	{
		&shell->env = allocate_env(envp, shell, i);
		env = env->next;
	}
	shell->env->next = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	copy_env(envp, &shell);
	while (shell.env.next != NULL)
	{
		printf("%s, %s\n", shell.env.name, shell.env.value);
		shell.env = *shell.env.next;
	}
	
	free_env(&shell.env, shell.env_start);
	// if (!shell.env)
	// 	return (ft_putstr_fd(
	// 			"mouliswag: fatal: environment allocation failed\n", 2), 1);
	// shell.cmds = NULL;
	// shell.last_exit = 0;
	// while (1)
	// 	parsing(&shell);
	return (0);
}
