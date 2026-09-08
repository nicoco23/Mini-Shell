/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:16:59 by ltournie          #+#    #+#             */
/*   Updated: 2026/09/08 16:42:41 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_SYNTAX_ERROR 2

# include <limits.h>
# include <linux/limits.h>
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
# include "libft/libft.h"

/* ======== LES STRUCTURES ======== */

/* ==== TYPES DE TOKENS ==== */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN, // redirection d entree     : <
	TOKEN_REDIR_OUT, // redirection de sortie   : >
	TOKEN_REDIR_APPEND, // redirection append   : >>
	TOKEN_REDIR_HEREDOC, // heredoc             : <<
	TOKEN_PIPE_IN, // entree de pipe 
	TOKEN_PIPE_OUT, // pipe to pipe
	TOKEN_PIPE_MID, // sortie de pipe
}	t_token_type;

/* ==== TOKEN ==== */ 

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quoted;
	struct s_token	*next;
}	t_token;

/* ===== REDIRECTION ===== */

typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	int				quoted;
	int				fd;
	int				fd_pipe[2];
	struct s_redir	*next;
}	t_redir;

/* ==== COMMANDE ==== */

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	char			*path;
	struct s_cmd	*next;
	int				*exit_status;
}	t_cmd;

/* ==== ENV ==== */

typedef struct s_env
{
	char			*name;
	char			*value;
	int				visibility;
	struct s_env	*next;
}	t_env;

/* ==== SHELL ==== */

typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmds;
	char	*line;
	pid_t	*pids;
	int		last_exit;
	int		saved_in;
	int		saved_out;
}	t_shell;

typedef struct s_wctx
{
	char	**word;
	t_shell	*shell;
	int		*quoted;
}	t_wctx;

/* ======= SIGNAUX ======= */

extern volatile sig_atomic_t	g_signal;

/* ======= FONCTION ======= */

/* parsing.c */
int			parsing(t_shell *shell);

/* lexer_utils.c*/
t_token		*new_token(t_token_type type, char *value);
void		token_add_back(t_token **list, t_token *new);
int			is_separator(char c);
int			append_char(char **word, char c);
int			read_quoted(char *line, int *i, char quote, t_wctx *ctx);

/* lexer.c */
t_token		*lexer(char *line, t_shell *shell);

/* expand.c */
int			expand_dollar(char *line, int *i, t_wctx *ctx);

/* cmd_builder.c */
t_cmd		*build_cmds(t_token *tokens);

/* cmd_redir.c */
int			add_redir(t_cmd *cmd, t_token_type type, char *target, int quoted);

/* syntax_check.c */
int			check_syntax(t_token *tokens);

/* parsing_free.c */
void		free_tokens(t_token *tokens);
void		free_cmds(t_cmd *cmds);

/* debug_cmds.c */
void		debug_print_cmds(t_cmd *cmds);
void		debug_print_env(char **env);

/* signal.c */
void		setup_signal_prompt(void);
void		setup_signal_exec(void);
void		setup_signal_exec2(void);
void		update_exit_status(t_shell *shell, int status);

/* signal_heredoc.c*/
void		setup_signal_heredoc(void);

/* signal_wait.c */
void		setup_signal_wait(void);

/* heredoc.c */
int			read_heredocs(t_cmd *cmds);

/* exec_utils.c*/
int			ft_listsize_cmd(t_cmd *lst);
void		free_tab(char **list);
void		print_error(char *str, int i);
void		close_if_open(int fd);
int			apply_redirs(t_cmd *cmd);

/* path_utils.c*/
char		*split_path(char *to_split, char *command);
char		*get_path(t_env *env, char *command);
void		set_path(char *arg, t_env *env, t_cmd *cmds);

/* cmd_exec.c */
void		exec(t_shell *shell);
void		print_error(char *str, int i);

/* exec_child.c */
void		child_process(t_cmd *cmd, t_shell *shell, int in_fd, int *pipe_fd);

/*cmd_check*/
int			is_builtin(char *name);
int			run_builtin(t_shell *shell, t_cmd *cmd);

/*cmd_cd*/
int			cmd_cd(t_shell *shell, t_cmd *cmd);
int			cmd_pwd(t_shell *shell);

/* cmd_echo.c */
int			cmd_echo(char **args);

/*cmd_env*/
int			cmd_env(t_env *env);

/* cmd_exit.c */
int			cmd_exit(t_shell *shell, char **args);

/* env_sort.c */
t_env		**sort_env_copy(t_env *lst, int *n);

/* env_list.c */
t_env		*env_new(char *name, char *value, int visibility);
t_env		*env_find(t_env *lst, const char *name);
char		*env_get(t_env *lst, const char *name);
void		env_add_back(t_env **lst, t_env *new);
void		env_clear(t_env **lst);

/* env_edit.c */
int			env_put(t_env **lst, char *name, char *value, int visibility);
int			env_put_entry(t_env **lst, char *entry, int visibility);
void		env_del(t_env **lst, const char *name);

/* env_init.c*/
void		init_shell_env(t_shell *shell);

/* env_convert.c */
int			env_size(t_env *lst);
char		**env_to_array(t_env *lst);
int			env_from_envp(char **envp, t_env **out);

/* cmd_export.c */
int			is_valid_id(const char *s);
int			cmd_export(t_shell *shell, char **args);
int			cmd_unset(char **args, t_shell *shell);

/* shell_free.c */
void		shell_free(t_shell *shell);
void		clean_exit(t_shell *shell, int code);

/* write_utils.c */
int			put_check(char *s, int fd);
int			putendl_check(char *s, int fd);
void		write_error(char *cmd);

#endif