/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:34:10 by djacobs           #+#    #+#             */
/*   Updated: 2023/06/19 12:34:11 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	close_window(t_xdata *param)
{
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	mlx_loop_end(param->mlx_ptr);
	return (0);
}

int	controls(int keysym, t_xdata *param)
{
	if (keysym == XK_Escape)
		close_window(param);
	else if (keysym == XK_w)
		param->Ximg->character.pos.y += 10;
	else if (keysym == XK_a)
		param->Ximg->character.pos.x -= 10;
	else if (keysym == XK_s)
		param->Ximg->character.pos.y -= 10;
	else if (keysym == XK_d)
		param->Ximg->character.pos.x += 10;
	return (0);
}
