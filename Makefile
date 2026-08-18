# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/02 15:02:23 by ltournie          #+#    #+#              #
#    Updated: 2026/08/17 18:43:11 by ntassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra -g3 -lreadline
SRC =	main.c						\
		src/parsing/parsing.c		\
		src/parsing/expand.c		\
		src/parsing/lexer_utils.c	\
		src/parsing/lexer.c			\
		src/parsing/cmd_builder.c	\
		src/parsing/cmd_redir.c		\
		src/parsing/syntax_check.c	\
		src/parsing/parsing_free.c	\
		
OBJ = $(SRC:%.c=%.o)
NAME = minishell
HEADER = -I include -I .
LINK = $(CC) $(CFLAGS)
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_LIB = -L$(LIBFT_DIR) -lft

.PHONY: all
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(LINK) $(OBJ) -o $(NAME) $(LIBFT_LIB)

.PHONY: libft
$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(LINK) $(HEADER) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_DIR) clean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

.PHONY: re
re: fclean $(NAME)