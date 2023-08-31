/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:42:29 by djacobs           #+#    #+#             */
/*   Updated: 2023/05/29 12:42:29 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*get map Length and Width*/
t_pos	get_map_lw(char	**map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y] != NULL)
		y++;
	while (map[0][x] != 0)
		x++;
	return ((t_pos){y, x});
}

int	is_map(char c)
{
	if (c == '0' || c == '1' || c == 'C' || c == 'P' || c == 'E' || c == '\n')
		return (1);
	return (0);
}

/*check map walls for holes and shape
int	map_walls(char **map, t_pos pos, int y, int x)
{
	int	wall;

	while (map[y] != NULL)
	{
		if (y < 2 || y == pos.y)
			wall = 0;
		while (map[y][x] != 0)
		{
			if (map[y][x] == '1')
				wall++;
			x++;
		}
		if ((wall != pos.x && (y == 0 || y == pos.y)) || \
		(x != pos.x || (map[y][x] != '1' && map[y][0] != '1')))
			return (err_msg("broken walls"), 0);
		if ((wall != pos.x && (y == 0 || y == pos.y)) || (y == pos.y - 1 && wall == ((pos.y - 2) * 2)) || x != pos.x )

		x = 0;
		y++;
	}
	if (pos.x == pos.y)
		return (err_msg("map is square"), 0);
	return (1);
}
*/
int	map_walls(char **map, t_pos pos, int y, int x)
{
	if (pos.y == pos.x)
		return(err_msg("map is square"), 0);
    while (x < pos.x) {
        if (map[0][x] != '1' || map[pos.y - 1][x] != '1')
            return (err_msg("broken walls on top/bottom"), 0);
        x++;
    }
    while (y < pos.y) {
        if (map[y][0] != '1' || map[y][pos.x - 1] != '1')
            return (err_msg("broken walls on left/right"), 0);
        y++;
    }
    return (1);
}

/*check for missing element*/
int	map_check(t_map *MapCheck, char *map, char **map_split)
{
	int	i;

	i = 0;
	while (map[i] != 0)
	{
		if (!is_map(map[i]))
			return (err_msg("bad character"), 0);
		if (map[i] == 'C')
			MapCheck->items++;
		else if (map[i] == 'E')
			MapCheck->exit++;
		else if (map[i] == 'P')
			MapCheck->character++;
		i++;
	}
	if ((MapCheck->exit != 1) || (MapCheck->character > 1 || \
	!MapCheck->character) || MapCheck->items < 1)
		return (err_msg("bad item or character or exit"), 0);
	if (!map_walls(map_split, get_map_lw(map_split), 0, 0))
		return (0);
	return (1);
}

/*
*	this function checks for the proper extension, that the files exists
*	then it'll check all the elements, for proper shape, that there is no hole
*	or that there is no stray walls, then it checks for the length and width
*	so that the map isn't too big
*/
int	map_parse(t_xdata *data, char *file)
{
	char	*map;

	if (!ber_file(file, ".ber"))
		return (err_msg("wrong file type"), 0);
	data->mp = (t_map){0, 0, 0, 0, {0, 0, 0, 0}};
	data->mp.fd = open(file, 0);
	if (data->mp.fd < 0)
		return (err_msg("no fd"), 0);
	gnl(data->mp.fd, &map, 0);
	if (map == NULL)
		return (close(data->mp.fd), err_msg("empty file"), 0);
	data->map = ft_split(map, '\n');
	if (data->map == NULL)
		return (close(data->mp.fd), 0);
	if (!map_check(&data->mp, map, data->map))
		return (free(map), close(data->mp.fd), free_split(data->map), 0);
	data->win_wl = get_map_lw(data->map);
	if (data->win_wl.x >= 64 || data->win_wl.y >= 42)
		return (err_msg("map too big"), free(map), \
		free_split(data->map), close(data->mp.fd), 0);
	if (!a_star(data->map, (t_star){get_pos(data->map, 'P'), \
	get_pos(data->map, 'E'), data->win_wl, 0, 0, 0, data->mp.items}))
		return (free(map), free_split(data->map), close(data->mp.fd), 0);
	data->player.pos = get_pos(data->map, 'P');
	return (free(map), close(data->mp.fd), 1);
}
