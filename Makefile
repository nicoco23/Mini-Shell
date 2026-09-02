# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/02 15:02:23 by ltournie          #+#    #+#              #
#    Updated: 2026/09/02 16:22:44 by ntassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDLIBS = -lreadline
SRC =	src/main.c					\
		src/parsing/parsing.c		\
		src/parsing/expand.c		\
		src/parsing/lexer_utils.c	\
		src/parsing/lexer.c			\
		src/parsing/cmd_builder.c	\
		src/parsing/cmd_redir.c		\
		src/parsing/syntax_check.c	\
		src/parsing/parsing_free.c	\
		src/parsing/debug_cmds.c	\
		src/parsing/heredoc.c		\
		src/signal/signal.c			\
		src/signal/signal_heredoc.c	\
		src/signal/signal_wait.c	\
		src/exec/path_utils.c		\
		src/exec/exec_utils.c		\
		src/exec/cmd_exec.c			\
		src/exec/cmd_check.c		\
		src/command/cmd_pwd.c		\
		src/command/cmd_cd.c		\
		src/command/cmd_echo.c		\
		src/command/cmd_env.c		\
		src/command/cmd_exit.c		\
		src/command/cmd_export.c	\
		src/command/env_utils.c		\
		src/command/env_sort.c		\
		
OBJ = $(SRC:src/%.c=obj/%.o)
DEPS = $(SRC:src/%.c=obj/%.d)
NAME = minishell
HEADER = -I include -I .
LINK = $(CC) $(CFLAGS)
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_LIB = -L$(LIBFT_DIR) -lft

.PHONY: all
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(LDLIBS)
	$(LINK) $(OBJ) -o $(NAME) $(LIBFT_LIB)

.PHONY: libft
$(LIBFT):
	make bonus -C $(LIBFT_DIR)

obj/%.o: src/%.c
	@if [ ! -d obj ]; then mkdir obj ; fi
	@if [ ! -d obj/exec ]; then mkdir obj/exec; fi
	@if [ ! -d obj/parsing ]; then mkdir obj/parsing; fi
	@if [ ! -d obj/command ]; then mkdir obj/command; fi
	@if [ ! -d obj/signal ]; then mkdir obj/signal; fi
	$(LINK) $(HEADER) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ) $(DEPS)
	rm -rf obj
	make -C $(LIBFT_DIR) clean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

.PHONY: re
re: fclean $(NAME)