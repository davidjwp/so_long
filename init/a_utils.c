/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:28:25 by djacobs           #+#    #+#             */
/*   Updated: 2023/06/29 13:28:27 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	lowest_h(t_node *list, t_pos pos, int Flow, int	Hlow)
{
	pos.x = INT_MAX;
	while (pos.g != pos.y)
	{
		if (list[pos.g].f == Flow && pos.g != pos.y)
		{
			if (list[pos.g].h < Hlow)
			{
				Hlow = list[pos.x].h;
				pos.x = pos.g;
			}
		}
		pos.g++;
	}
	return (pos.x);
}

int	lowest_f(t_node *list, t_pos pos)
{
	int	Flow;
	int	Hlow;

	Hlow = INT_MAX;
	Flow = list[pos.x].f;
	while (list[pos.x++].f != INT_MAX)
	{
		if (list[pos.x].f <= lowest_f)
		{
			Flow = list[pos.x].f;
			pos.y = pos.x;
		}
	}
	Hlow = lowest_h(list, pos, Flow, Hlow);
	if (Hlow == INT_MAX)
		return (pos.y);
	return (Hlow);
}

t_pos	get_pos(char **map, char c, t_pos pos)
{
	while (map[pos.y][pos.x] != c)
	{
		if (!map[pos.y])
		{
			pos.x = 0;
			pos.y++;
		}
		pos.x++;
	}
	return (pos);
}
