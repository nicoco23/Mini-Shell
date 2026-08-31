/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:16:59 by ltournie          #+#    #+#             */
/*   Updated: 2026/08/31 22:27:17 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_SYNTAX_ERROR 2

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
# include "libft/libft.h"

/* ======== LES STRUCTURES ========*/

// TYPES DE TOKENS
/*
** Enumeration de tous les types de tokens que le lexer peut generer
** Un token est considere comme l'unite minimale d'une ligne de commade.
*/
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

// TOKEN
/*
** Unite minimale produite par le lexer
*/
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quoted;
	struct s_token	*next;
}	t_token;
/* ===== REDIRECTION ===== */

/*
** Une redirection associée à une commande.
** Une commande peut avoir plusieurs redirections (liste chaînée).
**
** type   : le type de redirection (<, >, >>, <<)
** target : nom du fichier cible, ou délimiteur pour le heredoc
** quoted : 1 si le delimiteur du heredoc etait quote (desactive $ dans le corps)
** fd	  : descripteur ouvert par l'executor pour cette redirection
**			(-1 tant qu'elle n'a pas ete ouverte), utilise pour le dup2
** next   : redirection suivante sur la même commande
*/
typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	int				quoted;
	int				fd;
	int				fd_pipe[2];
	struct s_redir	*next;
}	t_redir;

/* ===== COMMANDE ===== */

/*
** Unité d'exécution : représente une commande simple dans un pipeline.
** Ex: dans "ls -la | grep foo", il y a deux t_cmd.
**
** args   : tableau de chaînes terminé par NULL.
**          args[0] = nom de la commande, args[1..n] = arguments.
**          Ce format est directement compatible avec execve().
** redirs : liste des redirections attachées à cette commande
** path	  : chemin resolu de l'executable (rempli par l'executor apres
			recherche dans PATH), NULL tant que non resolu
** next   : commande suivante dans le pipeline (NULL si dernière)
*/
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	char			*path;
	struct s_cmd	*next;
	int				*exit_status;
}	t_cmd;

/* ===== ÉTAT GLOBAL DU SHELL ===== */

/*
** Structure centrale passée à toutes les fonctions du shell.
** Elle regroupe tout ce dont le parser et l'executor ont besoin.
**
** env       : copie interne de envp faite au démarrage.
**             On ne touche JAMAIS à envp directement après l'init.
**             export/unset/cd modifient cette copie.
** cmds      : liste des commandes du pipeline courant,
**             produite par le parser et consommée par l'executor.
**             Libérée après chaque exécution.
** last_exit : code de retour de la dernière commande exécutée.
**             C'est ce que $? doit expanser.
*/
typedef struct s_shell
{
	char	**env;
	t_cmd	*cmds;
	int		last_exit;
}	t_shell;

typedef struct s_wctx
{
	char	**word;
	t_shell	*shell;
	int		*quoted;
}	t_wctx;

/* ===== VARIABLE GLOBALE SIGNAUX ===== */

/*
** La seule variable globale autorisée par le sujet.
** Le handler de signal y écrit le numéro du signal reçu (SIGINT, SIGQUIT...).
** La boucle main la lit pour réagir (réafficher le prompt, mettre à jour $?).
** volatile : force le compilateur à toujours relire la valeur en mémoire.
** sig_atomic_t : garantit que l'écriture est atomique (pas de corruption).
*/
extern volatile sig_atomic_t	g_signal;

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
char		*get_env_value(char **env, char *name);
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
char		*get_path(char **envp, char *command);
void		set_path(char *arg, char **envp, t_cmd *cmds);

/* cmd_exec.c */
void		exec(t_shell *shell);
void		print_error(char *str, int i);

/*cmd_check*/
int 		check_cmd(t_cmd *cmds, char **env);
int			is_builtin(char *name);
int			run_builtin_parent(t_shell *shell, t_cmd *cmd);

/*cmd_cd*/
int 		cmd_cd(t_cmd *cmds);
int 		cmd_pwd(void);

/* cmd_echo.c */
int			cmd_echo(char **args);

/*cmd_env*/
int 		cmd_env(char **env);

#endif