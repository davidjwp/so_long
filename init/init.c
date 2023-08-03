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

// typedef struct	s_xdata {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	void	*img_ptr;
// 	t_Ximg	*Ximg;
// 	t_pos	position;
// 	t_map	map;
// }				t_xdata;

void	render_init(t_xdata *data)
{
	int	width;
	int	height;

	data->Ximg->background = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/grass.xpm", &width, &height);
	data->Ximg->wall = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/walls.xpm", &width, &height);
	data->Ximg->exit = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/player.xpm", &width, &height);
	data->Ximg->item = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/objects.xpm", &width, &height);
	data->Ximg->character.img = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/player.xpm", &width, &height);
}

void	init_hooks(t_xdata *data, t_Ximg *ximg)
{
	data->Ximg = ximg;
	data->Ximg->character.pos = data->position;
	render_init(data);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0L, &close_window, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &controls, data);
}

void	destroy_all(t_xdata data)
{
	// mlx_destroy_image(data.mlx_ptr, data.Ximg->background);this is also causing a segfault, probably 
	// mlx_destroy_image(data.mlx_ptr, data.Ximg->character.img);because it's not actually set yet
	// mlx_destroy_image(data.mlx_ptr, data.Ximg->exit);
	// mlx_destroy_image(data.mlx_ptr, data.Ximg->item);
	// mlx_destroy_image(data.mlx_ptr, data.Ximg->wall);
	// mlx_destroy_display(data.mlx_ptr);
	mlx_loop_end(data.mlx_ptr);
	free(data.mlx_ptr);
}

//make sure to free data.map
int main(int argc, char **argv)
{
	t_xdata data;

	if (argc != 2)
		return (0);
	if (!map_parse(&data, &(t_map){argv[1], 0, 0, 0, 0, {0, 0, 0, 0}, 0, 0},\
	argv[1]))
		return (0);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (perror("Error mlx_init failed"), 0);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.map.width * BIT_SIZ ,\
	data.map.height * BIT_SIZ, "new_window");
	if (data.win_ptr == NULL)
		return (free(data.win_ptr), perror("Error new window"), 0);
	data.img_ptr = mlx_new_image(data.mlx_ptr, data.map.width * BIT_SIZ ,\
	data.map.height * BIT_SIZ);
	init_hooks(&data, &(t_Ximg){NULL, NULL, NULL, NULL,\
	(t_img){NULL, (t_pos){data.Ximg->character.pos.x, \
	data.Ximg->character.pos.y}}, (t_pos){0, 0}, (t_pos){0, 0}});
	mlx_loop(data.mlx_ptr);
	destroy_all(data);
	return (0);
}
