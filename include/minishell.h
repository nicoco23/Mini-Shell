/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:16:59 by ltournie          #+#    #+#             */
/*   Updated: 2026/06/02 17:37:00 by ntassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
}	t_token_type;

// TOKEN
/*
** Unite minimale produite par le lexer
*/
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;
/* ===== REDIRECTION ===== */

/*
** Une redirection associée à une commande.
** Une commande peut avoir plusieurs redirections (liste chaînée).
**
** type   : le type de redirection (<, >, >>, <<)
** target : nom du fichier cible, ou délimiteur pour le heredoc
** next   : redirection suivante sur la même commande
*/
typedef struct s_redir
{
	t_token_type	type;
	char			*target;
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
** next   : commande suivante dans le pipeline (NULL si dernière)
*/
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
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


/* ===== VARIABLE GLOBALE SIGNAUX ===== */

/*
** La seule variable globale autorisée par le sujet.
** Le handler de signal y écrit le numéro du signal reçu (SIGINT, SIGQUIT...).
** La boucle main la lit pour réagir (réafficher le prompt, mettre à jour $?).
** volatile : force le compilateur à toujours relire la valeur en mémoire.
** sig_atomic_t : garantit que l'écriture est atomique (pas de corruption).
*/
extern volatile sig_atomic_t g_signal;


# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

int parsing(void);

#endif