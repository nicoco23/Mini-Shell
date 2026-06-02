# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/02 15:02:23 by ltournie          #+#    #+#              #
#    Updated: 2026/06/02 16:18:50 by ntassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra -g3 -lreadline
SRC = main.c \
	parsing.c
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