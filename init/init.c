/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:18:50 by djacobs           #+#    #+#             */
/*   Updated: 2023/05/29 16:18:50 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	clean_map(t_node **map_node)
{
	t_pos	xy;

	xy.x = 0;
	xy.y = 0;
	while (map_node[xy.y] != NULL)
	{
		free(map_node[xy.y]);
		xy.y++;
	}
	free(map_node);
	map_node = NULL;
}

void	render_init(t_xdata *data)
{
	int	width;
	int	height;

	data->background = mlx_xpm_file_to_image(data->mlx_ptr, \
	"init/xpm/grass.xpm", &width, &height);
	data->wall = mlx_xpm_file_to_image(data->mlx_ptr, \
	"init/xpm/walls.xpm", &width, &height);
	data->exit = mlx_xpm_file_to_image(data->mlx_ptr, \
	"init/xpm/exit.xpm", &width, &height);
	data->item = mlx_xpm_file_to_image(data->mlx_ptr, \
	"init/xpm/objects.xpm", &width, &height);
	data->player.up = mlx_xpm_file_to_image(data->mlx_ptr, \
	"init/xpm/up.xpm", &width, &height);
	data->player.down = mlx_xpm_file_to_image(data->mlx_ptr, \
	"init/xpm/down.xpm", &width, &height);
	data->player.right = mlx_xpm_file_to_image(data->mlx_ptr, \
	"init/xpm/right.xpm", &width, &height);
	data->player.left = mlx_xpm_file_to_image(data->mlx_ptr, \
	"init/xpm/left.xpm", &width, &height);
}

void	init_hooks(t_xdata *data)
{
	data->player.steps = 0;
	data->player.items = 0;
	data->player.pos.y *= S_BIT;
	data->player.pos.x *= S_BIT;
	render_init(data);
	render_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->player.down, data->player.pos.x, data->player.pos.y);
	mlx_hook(data->win_ptr, DestroyNotify, 0L, &close_window, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &controls, data);
}

void	destroy_all(t_xdata data)
{
	mlx_destroy_image(data.mlx_ptr, data.background);
	mlx_destroy_image(data.mlx_ptr, data.player.down);
	mlx_destroy_image(data.mlx_ptr, data.player.up);
	mlx_destroy_image(data.mlx_ptr, data.player.left);
	mlx_destroy_image(data.mlx_ptr, data.player.right);
	mlx_destroy_image(data.mlx_ptr, data.exit);
	mlx_destroy_image(data.mlx_ptr, data.item);
	mlx_destroy_image(data.mlx_ptr, data.wall);
	mlx_destroy_image(data.mlx_ptr, data.img_ptr);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free_split(data.map);
	free(data.mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_xdata	data;

	if (argc != 2)
		return (0);
	if (!map_parse(&data, argv[1]))
		return (0);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (err_msg("mlx_init failed"), 0);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.win_wl.x * S_BIT, \
	data.win_wl.y * S_BIT, "new_window");
	if (data.win_ptr == NULL)
		return (free(data.win_ptr), err_msg("Error new window"), 0);
	data.img_ptr = mlx_new_image(data.mlx_ptr, data.win_wl.y * S_BIT, \
	data.win_wl.x * S_BIT);
	init_hooks(&data);
	mlx_loop(data.mlx_ptr);
	destroy_all(data);
	return (0);
}

/*
* The whole programs works by continuously looping while drawing the map and
* updating the characters position, for performance reasons it is better to
* just draw the map once and then simply draw the character as he moves 
* while replacing the item nodes with empty ones.
*
* Here is a step by step of each processes the program goes through
* 1 - the map is given as argument and parsed through to make sure it is 
*	correct, the maps have several requirements.
* 2 - once the map is found to be good, the a star algorithm will check if
*	there is a proper path to the end.
* 3 - if the path is good then the window is initialized and the image  
*	is created, the image is like the board on which the tiles are drawn,
*	the hooks are also set, these hooks will call a function once a key has
*	been pressed or the mouse clicked on an element of the window, before
*	the hooks though i initialize the images that will be drawn to the main
*	image then draw the map once and the character, then the hooks will draw
*	just what is needed to draw.
* 4 - now the game is initialized and you can play, the game exits when the
*	exit key is pressed or the cross is pressed or the character gets to the
*	exit when all collectibles have been collected, in order to exit the game
*	the main game loop is manually stopped, then every element is destroyed and
*	freed. 
*/