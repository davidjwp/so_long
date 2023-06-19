/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:09:55 by djacobs           #+#    #+#             */
/*   Updated: 2023/05/29 17:09:59 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_split(char **var)
{
	int	i;

	i = 0;
	while (var[i] != NULL)
	{
		free(var[i]);
		i++;
	}
	free(var);
}

int	gnl(int fd, char **str)
{
	char	*buf;
	char	c;
	int		n;
	int		i;

	i = 0;
	buf = malloc(sizeof(char) * BUFSIZ);
	n = read(fd, &c, 1);
	if (c == '\n')
		return (free(buf), *str == NULL);
	if (n)
		buf[i++] = c;
	while (n && c != 0)
	{
		n = read(fd, &c, 1);
		if (c == '\n' && buf[i - 2] == '\n')
			break;
		if (n != 0)
			buf[i] = c;
		i++;
	}
	buf[i - 1] = 0;
	buf[BUFSIZ - 1] = 0;
	*str = buf;
	return (1);
}

int	ber_file(char *mapName, char *extension)
{
	int	offset;

	offset = ft_strlen(mapName) - 4;
	while (mapName[offset] == *extension++ && mapName[offset])
		offset++;
	if (!mapName[offset])
		return (1);
	return (0);
}
