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

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0
# define IMG_WIDTH 32
# define IMG_HEIGHT 32
# define S_BIT	32
# define ERROR_FT_CPY ((void *)1)

typedef struct s_pos{
	int	y;
	int	x;
}			t_pos;

typedef struct s_node{
	int	visited;
	int	wall;
	int	item;
	int	x;
	int	y;
	int	f;
	int	g;
	int	h;
}			t_node;

typedef struct s_list {
	t_node			node;
	struct s_list	*next;
}			t_list;

typedef struct s_map {
	int	fd;
	int	exit;
	int	items;
	int	character;
	int	walls[4];
}				t_map;

typedef struct s_char {
	void	*img;
	void	*up;
	void	*down;
	void	*left;
	void	*right;
	t_pos	pos;
	int		items;
	int		steps;
}				t_char;

typedef struct s_xdata {
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*background;
	void	*wall;
	void	*exit;
	void	*item;
	char	**map;
	t_char	player;
	t_pos	pos;
	t_pos	img_siz;
	t_pos	win_wl;
	t_map	mp;
}				t_xdata;

typedef struct star_s {
	t_pos	start;
	t_pos	end;
	t_pos	mapwl;
	int		distance;
	int		exit;
	int		items;
	int		dt_items;
}				t_star;

//parsing
int		map_parse(t_xdata *data, char *file);
int		ber_file(char *mapName, char *extension);
int		a_star(char **map, t_star star);
int		add_list(t_list **list, t_node newnode);
int		is_map(char c);
int		wall_len(char *map);
int		map_shape(char **map, int i, int n);
t_node	*find_lowestf(t_list **list);
t_pos	get_pos(char **map, char c);
void	del_list(t_list **list);

//cleanup
void	free_split(char **var);
int		close_window(t_xdata *param);
void	xpm_image_fail(t_xdata *data);
int		empty_list(t_node *list, t_node default_node);
void	clean_map(t_node ***map_node);
int		free_map_list(t_node **map_node, t_star star, t_list **list);

//utils
int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
int		gnl(int fd, char **str, int i, int n);
void	err_msg(char *emsg);

//game
int		controls(int keysym, t_xdata *param);
void	render_map(t_xdata *data);

#endif