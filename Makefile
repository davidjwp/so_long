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

CC			= gcc

CFLAGS		= -g3 -Werror -Wall -Wextra

INCLUDE		= -I ./minilibx-linux

NAME		= so_long

LIBX		= -L ./minilibx-linux -lmlx -lm -lX11 -lXext

SRCS		= init/map.c utils/utils.c utils/ft_split.c init/init.c\
			 init/hooks.c init/render.c init/a_star.c init/a_utils.c\
			 init/map_utils.c

HEADER		= so_long.h

OBJS		= $(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBX) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

dclean: clean
	rm -f $(DEBUG_OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all
