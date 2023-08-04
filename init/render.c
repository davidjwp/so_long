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

void	render_map(t_xdata *data, char pos)
{
	if (pos == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->Ximg->wall, data->Ximg->pos.x, data->Ximg->pos.y);
	else if (pos == '0' || pos == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->Ximg->background, data->Ximg->pos.x, data->Ximg->pos.y);
	else if (pos == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->Ximg->exit, data->Ximg->pos.x, data->Ximg->pos.y);
	else if (pos == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->Ximg->item, data->Ximg->pos.x, data->Ximg->pos.y);
}

int	render(t_xdata *data)
{
	int	i;

	i = 0;
	data->Ximg->pos.x = 0;
	data->Ximg->pos.x = 0;
	while (data->map.map[i])
	{
		render_map(data, data->map.map[i]);
		if (data->map.map[i] == '\n')
		{
				data->Ximg->pos.x = 0;
				data->Ximg->pos.y += BIT_SIZ;
		}
		else
			data->Ximg->pos.x += BIT_SIZ;
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->Ximg->character.img, data->Ximg->character.pos.x, \
	data->Ximg->character.pos.y);
	return (0);
} 
// typedef struct	s_xdata {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	void	*img_ptr;
// 	t_Ximg	*Ximg;
// 	t_pos	position;
// 	t_map	map;
// }				t_xdata;