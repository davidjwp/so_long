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

void	render_init(t_xdata *data)
{
	int	width;
	int	height;

	data->background = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/grass.xpm", &width, &height);
	data->wall = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/walls.xpm", &width, &height);
	data->exit = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/exit.xpm", &width, &height);
	data->item = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/objects.xpm", &width, &height);
	data->player.up = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/up.xpm", &width, &height);
	data->player.down = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/down.xpm", &width, &height);
	data->player.right = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/right.xpm", &width, &height);
	data->player.left = mlx_xpm_file_to_image(data->mlx_ptr,\
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
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

//make sure to free data.map
int main(int argc, char **argv)
{
	t_xdata data;

	if (argc != 2)
		return (0);
	if (!map_parse(&data, argv[1]))
		return (0);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (err_msg("mlx_init failed"), 0);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.WinWL.x * S_BIT ,\
	data.WinWL.y * S_BIT, "new_window");
	if (data.win_ptr == NULL)
		return (free(data.win_ptr), err_msg("Error new window"), 0);
	data.img_ptr = mlx_new_image(data.mlx_ptr, data.WinWL.y * S_BIT ,\
	data.WinWL.x * S_BIT);
	init_hooks(&data);
	mlx_loop(data.mlx_ptr);
	destroy_all(data);
	return (0);
}
