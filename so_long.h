/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:13:12 by djacobs           #+#    #+#             */
/*   Updated: 2023/05/16 10:13:14 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SO_LONG_H
# define SO_LONG_H

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <fcntl.h>

#define RED 0XFF0000
#define GREEN 0X00FF00
#define WHITE 0XFFFFFF
#define WIN_WIDTH 720
#define WIN_HEIGHT 480
#define	IMG_WIDTH (WIN_WIDTH - 240) / 10
#define IMG_HEIGHT WIN_HEIGHT / 10
#define NULL (void *)0

typedef enum {
	true = 1,
	false = 0
}		bool;

typedef struct s_pos{
	int x;
	int y;
}			t_pos;

typedef struct	s_map {
	char	*map;
	int 	fd;
	int		exit;
	int		item;
	int		character;
	int 	walls[4];
	int 	height;
	int 	width;
} 				t_map;

typedef struct	s_img {
	void	*img;
	int		width;
	int		height;
	t_pos	pos;
}				t_img;

typedef struct	s_Ximg {
	void	*background;
	void	*wall;
	void	*exit;
	void	*item;
	t_img	character;
	t_pos	pos;
}				t_Ximg;

typedef struct	s_xdata {
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	t_Ximg	*Ximg;
	t_pos	position;
	t_map	map;
}				t_xdata;


typedef struct s_rect{
	t_pos position;
	int width;
	int height;
	int color;
}	t_rect;

//utils
int		get_height(char *str);
int		get_width(char *str);
int		ft_strlen(char *str);
char	**ft_split(char const *s, char c);
void	free_split(char **var);
int		map_parse(t_xdata *data, t_map *MapCheck, char *file);
int		gnl(int fd, char **str);
int		ber_file(char *mapName, char *extension);
int		close_window(t_xdata *param);
int		controls(int keysym, t_xdata *param);
int		render(t_xdata *data);

#endif