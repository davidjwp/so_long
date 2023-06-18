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

void	init_hooks(t_xdata data)
{
	data.Ximg->pos.x = 0;
	data.Ximg->pos.y = 0; 
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, DestroyNotify, 0L, &close_window, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &controls, &data);
}

void	destroy_all(t_xdata data)
{
	mlx_destroy_image(data.mlx_ptr, data.Ximg->background.image);
	mlx_destroy_image(data.mlx_ptr, data.Ximg->character.image);
	mlx_destroy_image(data.mlx_ptr, data.Ximg->exit.image);
	mlx_destroy_image(data.mlx_ptr, data.Ximg->item.image);
	mlx_destroy_image(data.mlx_ptr, data.Ximg->wall.image);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}

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
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "new_window");
	if (data.win_ptr == NULL)
		return (free(data.win_ptr), perror("Error new window"), 0);
	init_hooks(data);
	mlx_loop(data.mlx_ptr);
	// destroy_all(data); not until everything is set
	return (0);
}
