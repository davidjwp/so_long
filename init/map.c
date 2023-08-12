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

t_pos	get_map_LW(char	**map)
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

/*
** checks that the walls are not missing, are the proper length and that the
** map isn't a square
*/
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
		if ((wall != pos.x && (y == 0 || y == pos.y)) ||\
		(x != pos.x || (map[y][x] != '1' && map[y][0] != '1')))
			return (err_msg("broken walls"), 0);
		x = 0;
		y++;
	}
	if (pos.x == pos.y)
		return (err_msg("map is square"), 0);
	return (1);
}

/*
** check for missing elements and walls
*/
int	map_check(t_map *MapCheck, char *map, char **map_split)
{
	int	i;

	i = 0;
	while (map[i] != 0)
	{
		if (!is_map(map[i]))
			return (0);
		if (map[i] == 'C')
			MapCheck->items++;
		else if (map[i] == 'E')
			MapCheck->exit++;
		else if (map[i] == 'P')
			MapCheck->character++;
		i++;
	}
	if ((MapCheck->exit < 1 || !MapCheck->exit) ||\
	(MapCheck->character > 1 || !MapCheck->character) ||\
	MapCheck->items < 1)
		return (err_msg("bad item or character or exit"), 0);
	if (!map_walls(map_split, get_map_LW(map_split), 0, 0))
		return (0);
	return (1);
}

/*
** map_parse contains all the other map parsing utilities, first i open the
** the file and read it, with gnl this way i have the whole map in an array
** and everytime it is more conveniant to split it i use ft_split
*/
int	map_parse(t_xdata *data, char *file)
{
	char	*map;

	if (!ber_file(file, ".ber"))
		return (err_msg("wrong file type"), 0);
	data->Map = (t_map){0, 0, 0, 0, {0, 0, 0,0}};
	data->Map.fd = open( file, 0);
	if (data->Map.fd < 0)
		return (err_msg("no fd"), 0);
	gnl(data->Map.fd, &map);
	if (map == NULL)
		return (close(data->Map.fd), err_msg("empty file"), 0);
	data->map = ft_split(map, '\n');
	if (!map_check(&data->Map, map, data->map))
		return (free(map), close(data->Map.fd), free_split(data->map), 0);
	data->WinWL = get_map_LW(data->map);
	if (ft_strlen(data->map[0]) >= 64)
		return (err_msg("map too big"), free(map),\
		free_split(data->map), close(data->Map.fd), 0);
	if (!a_star(data->map, (star_t){get_pos(data->map, 'P'),\
	get_pos(data->map,'E'), data->WinWL, 0}))
		return(err_msg("wrong path"), free(map), free_split(data->map),\
		close(data->Map.fd), 0);
	data->player.pos = get_pos(data->map, 'P');
	return (free(map), close(data->Map.fd), 1);
}
