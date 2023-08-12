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

void	render_unit(t_xdata *data, char pos)
{
	if (pos == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->wall, data->pos.x, data->pos.y);
	else if (pos == '0' || pos == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->background, data->pos.x, data->pos.y);
	else if (pos == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->exit, data->pos.x, data->pos.y);
	else if (pos == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->item, data->pos.x, data->pos.y);
}

void render_map(t_xdata *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	data->pos.x = 0;
	data->pos.y = 0;
	if (data->map[data->player.pos.y / S_BIT][data->player.pos.x / S_BIT]\
	 == 'C')
	data->map[data->player.pos.y / S_BIT][data->player.pos.x / S_BIT] = '0';
	while (data->map[y] != NULL)
	{
		while (data->map[y][x] != 0)
		{
			render_unit(data, data->map[y][x]);
			data->pos.x += S_BIT;
			x++;
		}
		data->pos.y += S_BIT;
		data->pos.x = 0;
		y++;
		x = 0;
	}
}
