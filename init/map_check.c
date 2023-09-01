# include "../so_long.h"

int	wall_len(char *map)
{
	int	i;

	i = 0;
	while (map[i] && map[i] != '\n' )
		i++;
	return (i);
}

void	map_shape(char **map, int flen, int i, int n)// this doesn't seem to work because of the map NULL condition is not found in map_parse
{
	while (map[0][i])
	{
		if (map[0][i] == '\n' && n != flen)
		{
			free(*map);
			*map = NULL;
		}
		if (*map == NULL)
			break ;
		if (map[0][i] != '\n')
			n++;
		else
			n = 0;
		i++;
	}
	if (*map == NULL)
		err_msg("bad map shape");
}

// void	map_shape(char *map, int flen, int i, int n)
// {
// 	while (map[i])
// 	{
// 		while (map[i] != '\n')
// 		{
// 			if (map == NULL)
// 				break ;
// 			if (!is_map(map[i]))
// 				map = NULL;
// 			n++;
// 			i++;
// 		}
		
// 	}
// 	if (map == NULL)
// 		err_msg("bad map shape");
// }