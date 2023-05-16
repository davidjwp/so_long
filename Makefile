# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djacobs <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 10:20:11 by djacobs           #+#    #+#              #
#    Updated: 2023/05/16 10:20:13 by djacobs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= clang

CFLAGS		= -g3 #-Werror -Wall -Wextra

LINKER		= -L ./minilibx-linux

INCLUDE		= -I ./minilibx-linux

NAME		= test

LIBX		= -lm -lX11 -lXext -lmlx

SRCS		= test.c

HEADER		= so_long.h

OBJS		= $(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LINKER) $(INCLUDE) $(OBJS) $(LIBX) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all
