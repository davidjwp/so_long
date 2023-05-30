# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djacobs <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 10:20:11 by djacobs           #+#    #+#              #
#    Updated: 2023/05/30 08:35:57 by djacobs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= clang

CFLAGS		= -g3 #-Werror -Wall -Wextra

LINKER		= -L ./minilibx-linux

INCLUDE		= -I ./minilibx-linux

DEBUG		= tdebug

DEBUG_SRCS	= minilibx-linux/mlx_init.c minilibx-linux/mlx_loop.c minilibx-linux/mlx_loop_hook.c \
			minilibx-linux/mlx_new_window.c minilibx-linux/mlx_key_hook.c minilibx-linux/mlx_destroy_window.c 

DEBUG_OBJS	= $(DEBUG_SRCS:.c=.o)

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

debug:$(DEBUG)

$(DEBUG):$(OBJS) $(DEBUG_OBJS)
	$(CC) $(CFLAGS) $(LINKER) $(INCLUDE) $(OBJS) $(DEBUG_OBJS) $(LIBX) -o $(DEBUG)

dclean: clean
	rm -f $(DEBUG_OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all
