/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:01:28 by djacobs           #+#    #+#             */
/*   Updated: 2023/06/19 12:01:29 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//missing the item
void	render_map(t_xdata *data, char pos)
{
	if (pos == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->Ximg->wall, data->Ximg->pos.x, data->Ximg->pos.y);
	else if (pos == '0')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->Ximg->background, data->Ximg->pos.x, data->Ximg->pos.y);
	else if (pos == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->Ximg->character.img, data->Ximg->character.pos.x,\
		data->Ximg->character.pos.x);
	else if (pos == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->Ximg->exit, data->Ximg->pos.x, data->Ximg->pos.y);
}

void	render_init(t_xdata *data)
{
	int	width;
	int	height;

	data->Ximg->background = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/background.xpm", &width, &height);
	data->Ximg->wall = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/wall.xpm", &width, &height);
	data->Ximg->exit = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/exit.xpm", &width, &height);
	data->Ximg->item = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/item.xpm", &width, &height);
	data->Ximg->character.img = mlx_xpm_file_to_image(data->mlx_ptr,\
	"init/xpm/character.xpm", &width, &height);
}

int	render(t_xdata *data)
{
	int	i;

	i = 0;
	render_init(data);
	while (data->map.map[i])
	{
		if (data->map.map[i] != '\n')
			render_map(data, data->map.map[i]);
		else
		{
			data->Ximg->pos.y += IMG_HEIGHT;
			data->Ximg->pos.x = 0;
		}
		data->Ximg->pos.x += IMG_WIDTH;
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr,\
	0, 0);
	return (0);
}
