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
	mlx_loop_end(param->mlx_ptr);
	return (0);
}

char	*itoa(int n, char *str)
{
	int	number;
	int	i;

	i = 0;
	number = n;
	while (number / 10)
	{
		number /= 10;
		i++;
	}
	str = malloc((i + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i + 1] = 0;
	while (i)
	{
		str[i--] = "0123456789"[n % 10];
		n = n / 10;
	}
	str[i] = "0123456789"[n % 10];
	return (str);
}

int	put_steps(t_xdata *prm, int keysym, t_pos cpos)
{
	char	*str;
	int		steps;
	int		size;

	if ((keysym == XK_w && (prm->map[(cpos.y - 1) / S_BIT][cpos.x / S_BIT] == \
	'1')) || (keysym == XK_s && prm->map[(cpos.y / S_BIT) + 1][cpos.x / S_BIT] \
	== '1') || (keysym == XK_a && prm->map[cpos.y / S_BIT][(cpos.x - 1) / S_BIT \
	] == '1') || (keysym == XK_d && prm->map[cpos.y / S_BIT][(cpos.x / S_BIT) + \
	1] == '1'))
		return (0);
	prm->player.steps++;
	size = 1;
	str = NULL;
	steps = prm->player.steps;
	while (steps / 10)
	{
		steps /= 10;
		size++;
	}
	str = itoa(prm->player.steps, str);
	if (str == NULL)
		return (err_msg("hooks itoa malloc fail"), \
		mlx_loop_end(prm->mlx_ptr), 0);
	write (1, "steps: ", 7);
	return (write (1, str, size), write (1, "\n", 1), free(str), 0);
}

void	render_player(int keysym, t_xdata *prm)
{
	if (keysym == XK_w)
		mlx_put_image_to_window(prm->mlx_ptr, prm->win_ptr, \
		prm->player.up, prm->player.pos.x, prm->player.pos.y);
	else if (keysym == XK_a)
		mlx_put_image_to_window(prm->mlx_ptr, prm->win_ptr, \
		prm->player.left, prm->player.pos.x, prm->player.pos.y);
	else if (keysym == XK_s)
		mlx_put_image_to_window(prm->mlx_ptr, prm->win_ptr, \
		prm->player.down, prm->player.pos.x, prm->player.pos.y);
	else if (keysym == XK_d)
		mlx_put_image_to_window(prm->mlx_ptr, prm->win_ptr, \
		prm->player.right, prm->player.pos.x, prm->player.pos.y);
	if (prm->player.items == prm->mp.items && \
	prm->map[prm->player.pos.y / S_BIT][prm->player.pos.x / S_BIT] == 'E')
		mlx_loop_end(prm->mlx_ptr);
}

int	controls(int keysym, t_xdata *prm)
{
	if (keysym == XK_Escape)
		close_window(prm);
	if (keysym == XK_w || keysym == XK_a || keysym == XK_d || keysym == XK_s)
		put_steps(prm, keysym, prm->player.pos);
	if (keysym != XK_w && keysym != XK_a && keysym != XK_s && keysym != XK_d)
		return (0);
	else if (keysym == XK_w && prm->map[(prm->player.pos.y - 1) / S_BIT] \
	[prm->player.pos.x / S_BIT] != '1')
		prm->player.pos.y -= S_BIT;
	else if (keysym == XK_a && prm->map[prm->player.pos.y / S_BIT] \
	[(prm->player.pos.x - 1) / S_BIT] != '1')
		prm->player.pos.x -= S_BIT;
	else if (keysym == XK_s && prm->map[(prm->player.pos.y / S_BIT) + 1] \
	[prm->player.pos.x / S_BIT] != '1')
		prm->player.pos.y += S_BIT;
	else if (keysym == XK_d && prm->map[prm->player.pos.y / S_BIT] \
	[(prm->player.pos.x / S_BIT) + 1] != '1')
		prm->player.pos.x += S_BIT;
	if (prm->map[prm->player.pos.y / S_BIT][prm->player.pos.x / S_BIT] == 'C')
	{
		prm->map[prm->player.pos.y / S_BIT][prm->player.pos.x / S_BIT] = '0';
		prm->player.items++;
	}
	return (render_map(prm), render_player(keysym, prm), 0);
}
