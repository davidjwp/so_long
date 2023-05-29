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
** 1.has to have four walls and be closed if not error message 
** 2.has to have at least one item to collect, one exit and one character start, no double exit or character
** 3.has to be a rectangle, all horizontal lines have the same length, all vertical lines have the same 
** 4.has to be a valid path to the exit
** 5.also make sure that the map isn't too big
*/

int	is_map(char c)
{
	if (c != '0' || c != '1' || c != 'C' || c != 'P' || c != 'E' || c != '\n')
		return (0);
	return (1);
}

/*
** the way i interpret the rule about needing to have a 
** "valid path (i.e. a path you can take)" is that it should be taken as 
** an error that you have a map in which you are surrounded by walls, the other
** way i thought about it was that regardless of the map if there is no way
** to get to the exit you should take that as an error, since that sounds way
** too complicated i decided to go with my simpler explanation
** so this is what this function does
*/
int	map_path(char **map, t_pos pos)
{
	while (map[pos.y][pos.x] != 'P')
	{
		if (map[pos.y][pos.x++] == 0)
		{
			pos.y++;
			pos.x = 0;
		}
	}
	if (map[pos.y][pos.x + 1] == '0' || map[pos.y][pos.x - 1] == '0' ||\
	map[pos.y + 1][pos.x] == '0' || map[pos.y - 1][pos.x] == '0')
		return (free_all_split(map), 1);
	return (free_all_split(map), 0);
}

// map_walls function check that every wall is closed and same length
int	map_walls(t_map *MapVar, char **map, int y, int x)
{
	int	wall;

	while (map[y] != NULL)
	{
		wall = 0;
		while (map[y][x] && map[y][x] != 0)
		{
			if (map[y][x] == '1' && (y == 0 || y == MapVar->height))
				wall++;
			else if (map[y][x] == '1' && (y > 0 && y < MapVar->height))
				wall++;
			x++;
		}
		if ((wall != MapVar->width && (y == 0 || y == MapVar->height)) ||\
		(wall != (MapVar->height - 2) * 2 && (y > 0 && y < MapVar->height)))
			return (Perror ("Error wrong wall size"), free_all_split(map), 0);
		x = 0;
		y++;
	}
	return (free_all_split(map), 1);
}

//map_check checks non-valid elements and requirements, also checks walls
int	map_check(t_map *MapCheck, char *map)
{
	int	i;

	i = 0;
	while (map[i] != '/0')
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
		return (0);
	if (!map_walls(&(t_map){0, 0, 0, 0, {0,0,0,0}, get_height(map),\
	get_width(map)}, ft_split(map, '\n'), 0, 0))
		return (0);
	return (1);
}


//this is probably not a good idea you should do a gnl on this to make sure to get all the map 
//basically i just need the map in one string from the file descriptor, so i need to read the file 
//descriptor into a string but i don't have the length of that string  
int	map_parse(t_xdata *data, t_map *MapCheck, char *file)
{
	char	*map;

	data->map = *MapCheck;
	data->map.fd = open( file, __O_CLOEXEC);
	while (gnl(&map))
	{

	}
	if (!map_check(&data->map, buf))
		return (close(data->map.fd),0);
	if (!map_path(ft_split(file, '\n', (t_pos){0,0})))
	{}
}
