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
	if (c == '0' || c == '1' || c == 'C' || c == 'P' || c == 'E' || c == '\n')
		return (1);
	return (0);
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
		return (1);
	return (0);
}

/*
** map_walls function checks the walls, for that it uses a nasty conditional 
** that is almost unreadable map_walls function check that every wall is 
** closed and same length to dissect with a nice headache at the end
**
** so let me dissect it line by line :
** 1. this checks the horizontal walls for proper width
** 2. this checks the vertical walls for the right the first and last must be a wall
** 3. if the index count isn't the right amount or the last or first element of the line isn't a wall
*/


//one of the reason why this fails is because on the second row it goes in the loop again
//i think somewhere in the code you added something that shouldn't be there 
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
		((wall != (MapVar->height - 2) * 2) && y == MapVar->height -1) ||\
		(x != MapVar->width || (map[y][x] != '1' && map[y][0] != '1')))
			return (perror ("Error wrong wall size"),\
			free(MapVar->name), free_split(map), 0);
		x = 0;
		y++;
	}
	return (free_split(map), 1);
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
		return (0);
	map_split = ft_split(map, '\n');
	if (!map_walls(&(t_map){map, 0, 0, 0, 0, {0, 0, 0, 0}, get_height(map),\
	get_width(map)}, map_split, 0, 0))
		return (free(map), free_split(map_split),0);
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

	data->map = *MapCheck;
	data->map.fd = open( file, __O_CLOEXEC);
	gnl(data->map.fd, &map);
	if (!map_check(&data->map, map))
		return (free(map), close(data->map.fd),0);
	map_split = ft_split(map, '\n');
	if (!map_path(map_split, (t_pos){0, 0}))
		return(free(map), free_split(map_split), close(data->map.fd), 0);
	return (free_split(map_split), 1);
}
