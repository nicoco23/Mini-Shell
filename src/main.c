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
	t_env	*env;
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

static int get_env_value(t_env *env, char *line)
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
	while(line[i + j] != '\0') //moi je veux ce qui est apres mon espace je veux pas enlever je veux copier
		j++;
	env->value = malloc(sizeof(char *) * (j + 1));
	if (!env->value)
		return (-1);
	strcpy(env->value, &line[i]);
	// env->value = *line; 
	// printf("test\n");
	// j = 0;
	// printf("test\n"); //print 
	// while (line[i] != '\0')
	// {
	// 	env->value[j] = line[i];
	// 	i++;
	// }
	// printf("test\n"); // print pas
	// env->value[j] = '\0';
	return (0);
}

static int get_env_name(t_env *env, char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0' && line[i] != '=')
		i++;
	env->name = malloc(sizeof(char *) * (i + 1));
	if (!env->name)
		return (-1);
	strlcpy(env->name, line, i);
	// i = 0;
	// while (line[i] != '\0' || line[i] != '=')
	// {
	// 	env->name[i] = line[i];
	// 	i++;
	// }
	// env->name[i] = '\0';
	return (0);
}

t_env	*allocate_env(char **envp, t_shell *shell, int i)
{
	t_env *env;
	
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	if (get_env_value(env, envp[i]) == -1 || get_env_name(env, envp[i]) == -1)
		return (free_env(env, shell->env_start), NULL);
	return (env);
}

static void *copy_env(char **envp,t_shell *shell)
{
	int		i;
	t_env *new;
	t_env *last;

	i = 0;
	shell->env = NULL;
	shell->env_start = NULL;
	// shell->env = allocate_env(envp, shell, i);
	// shell->env_start = &shell->env; 
	printf("test\n"); 
	while (envp[i] != NULL)
	{
		new = allocate_env(envp, shell, i);
		if (!shell->env)
			shell->env = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	shell->env_start = shell->env;
	printf("test\n");
	// shell->env->next = NULL;
	printf("test\n");
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	copy_env(envp, &shell);
	while (shell.env->next != NULL)
	{
		printf("%s, %s\n", shell.env->name, shell.env->value);
		shell.env = shell.env->next;
	}
	
	free_env(shell.env, shell.env_start);
	// if (!shell.env)
	// 	return (ft_putstr_fd(
	// 			"mouliswag: fatal: environment allocation failed\n", 2), 1);
	// shell.cmds = NULL;
	// shell.last_exit = 0;
	// while (1)
	// 	parsing(&shell);
	return (0);
}
