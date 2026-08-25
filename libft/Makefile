# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntassin <ntassin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 15:43:30 by ltournie          #+#    #+#              #
#    Updated: 2026/08/25 18:11:27 by ntassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra
SRC =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_countword.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c
SRC_BONUS =	ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c
SRC_OTHER =	ft_printf.c \
			ft_putchar.c \
			ft_putnbr.c \
			ft_putnbrhex.c \
			ft_putnbrhexp.c \
			ft_putnbru.c \
			ft_putpoint.c \
			ft_putstr.c \
			get_next_line.c \
			get_next_line_utils.c
OBJ = $(SRC:%.c=%.o)
OBJ_BONUS = $(SRC_BONUS:%.c=%.o)
OBJ_OTHER = $(SRC_OTHER:%.c=%.o)
NAME = libft.a
HEADER = libft.h
LINK = $(CC) $(CFLAGS)
LINK_LIB = ar -rc
RM = rm -f

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ) $(OBJ_OTHER)
	$(LINK_LIB) $(NAME) $(OBJ) $(OBJ_OTHER)

%.o: %.c $(HEADER)
	$(LINK) -I . -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ) $(OBJ_BONUS) $(OBJ_OTHER)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME) $(NAME_BONUS) 

.PHONY: re
re: fclean $(NAME)

.PHONY: bonus
bonus:$(OBJ) $(OBJ_BONUS) $(OBJ_OTHER)
	$(LINK_LIB) $(NAME) $(OBJ) $(OBJ_BONUS) $(OBJ_OTHER)
