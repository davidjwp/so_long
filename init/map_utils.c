/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:27:06 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/01 15:27:07 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	wall_len(char *map)
{
	int	i;

	i = 0;
	while (map[i] && map[i] != '\n' )
		i++;
	return (i);
}

int	map_clean(char **map, int i, int n)
{
	char	*mapcpy;

	mapcpy = malloc(sizeof(char) * BUFSIZ);
	if (mapcpy == NULL)
		return (err_msg("map_clean malloc fail"), 0);
	while (map[0][i] != 'P' && map[0][i])
		i++;
	if (!map[0][i])
		return (err_msg("no player"), free(mapcpy), 0);
	while ((map[0][i] != '\n' || map[0][i - 1] != '\n') && (*map != NULL && i))
		i--;
	while ((((map[0][i] != '\n' || map[0][i + 1] != '\n') && (map[0][i] != '\n' \
	|| map[0][i + 1] != 0)) && map[0][i] && *map != NULL))
	{
		if (map[0][i] == '\n' && !n)
			i++;
		mapcpy[n] = map[0][i];
		n++;
		i++;
	}
	mapcpy[n] = 0;
	*map = mapcpy;
	return (1);
}

int	map_shape(char **map, int i, int n)
{
	int	flen;

	if (!map_clean(map, 0, 0))
		return (*map = NULL, 0);
	flen = wall_len(*map);
	while (map[0][i] != 0)
	{
		if (map[0][i] != '\n')
			n++;
		else
			n = 0;
		i++;
		if ((map[0][i] == '\n' || !map[0][i]) && n != flen)
		{
			free(*map);
			*map = NULL;
			break ;
		}
	}
	if (*map == NULL)
		return (err_msg("bad map shape"), 0);
	return (1);
}
