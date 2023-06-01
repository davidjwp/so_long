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
	mlx_loop_hook(data.mlx_ptr, &render, &mlx);
	mlx_hook(data.win_ptr, DestroyNotify, 0L, &close_my_window, &mlx);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &controls, &mlx);
}

void	destroy_all(t_xdata data)
{
	mlx_destroy_image(data.mlx_ptr, data.img.image);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}

void	init_imgs(t_xdata data, )
{

}

int main(int argc, char **argv)
{
    t_xdata data;

	if (!map_parse(&data, &(t_map){argv[1], 0, 0, 0, 0, {0, 0, 0, 0}, 0, 0},\
	argv[1]))
		return (0);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (perror("Error mlx_init failed"), 0);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "new_window");
	if (data.win_ptr == NULL)
		return (free(data.win_ptr), perror("Error new window"), 0);
	// data.img.image = mlx_new_image(mlx.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	// data.img.addr = mlx_get_data_addr(mlx.img.image, &mlx.img.bpp, &mlx.img.line_len, &mlx.img.endian);
	// data.xpm.img = (mlx.win_ptr, "untitled.xpm", mlx.xpm.width, mlx.xpm.height);
	init_hooks(data);
	mlx_loop(data.mlx_ptr);
	destroy_all(data);
	return (0);
}