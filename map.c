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

#include "so_long.h"

/*
** filters the map to only look for a couple characters
*/
int	is_map(char c)
{
	if (c == '0' || c == '1' || c == 'C' || c == 'P' || c == 'E' || c == '\n')
		return (1);
	return (0);
}

/*
** map_walls function checks the walls, for that it uses a nasty conditional
** that is almost unreadable, map_walls function checks that every wall is 
** closed and same length to dissect with a nice headache at the end
**
** so let me dissect it line by line :
** 1. this checks the horizontal walls for proper width
** 2. this checks the vertical walls for the right the first and last must be a wall
** 3. if the index count isn't the right amount or the last or first element of the line isn't a wall
*/
int	map_walls(t_map *MapVar, char **map, int y, int x)
{
	int	wall;

	while (map[y] != NULL)
	{
		if (y < 2 || y == MapVar->height)
			wall = 0;
		while (map[y][x] != 0)
		{
			if (map[y][x] == '1')
				wall++;
			x++;
		}
		if ((wall != MapVar->width && (y == 0 || y == MapVar->height)) ||\
		(x != MapVar->width || (map[y][x] != '1' && map[y][0] != '1')))
			return (perror ("Error bad walls"), 0);
		x = 0;
		y++;
	}
	return (1);
}

//map_check checks non-valid elements and requirements, also checks walls
int	map_check(t_map *MapCheck, char *map)
{
	char	**map_split;
	int	i;

	i = 0;
	while (map[i] != 0)
	{
		if (!is_map(map[i]))
			return (0);
		if (map[i] == 'C')
			MapCheck->item++;
		else if (map[i] == 'E')
			MapCheck->exit++;
		else if (map[i] == 'P')
			MapCheck->character++;
		i++;
	}
	if ((MapCheck->exit > 1 || !MapCheck->exit) ||\
	(MapCheck->character > 1 || !MapCheck->character) ||\
	MapCheck->item < 1)
		return (perror("Error bad item or character or exit"), 0);
	map_split = ft_split(map, '\n');
	if (!map_walls(&(t_map){map, 0, 0, 0, 0, {0, 0, 0, 0}, get_height(map),\
	get_width(map)}, map_split, 0, 0))
		return (free_split(map_split), 0);
	return (free_split(map_split), 1);
}

/*
** map_parse contains all the other map parsing utilities, first i open the
** the file and read it, with gnl this way i have the whole map in an array 
** and everytime it is more conveniant to split it i use ft_split
*/
int	map_parse(t_xdata *data, t_map *MapCheck, char *file)
{
	char	**map_split;
	char	*map;

	if (!ber_file(MapCheck->map, ".ber"))
		return (perror("Error wrong file type"), 0);
	data->map = *MapCheck;
	data->map.fd = open( file, 0);
	if (data->map.fd < 0)
		return (perror("Error"), 0);
	gnl(data->map.fd, &map);
	if (map == NULL)
		return (close(data->map.fd), perror("Error nothing in file"), 0);
	if (!map_check(&data->map, map))
		return (free(map), close(data->map.fd),0);
	map_split = ft_split(map, '\n');
	if (ft_strlen(map_split[0]) >= 64)
		return (perror("Error map too big"), free(map), free_split(map_split)\
		, close(data->map.fd), 0);
	if (a_star(map_split, (star_t){false, false, 0, 0, 0, INT_MAX, INT_MAX}))
		return(free(map), free_split(map_split), close(data->map.fd), 0);
	data->map.map = map;
	return (free_split(map_split), close(data->map.fd), 1);
}
