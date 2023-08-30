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

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != 0)
		len++;
	return (len);
}

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

int	gnl(int fd, char **str, int i)
{
	char	*buf;
	char	c;
	int		n;

	buf = malloc(sizeof(char) * BUFSIZ);
	if (buf == NULL)
		return (*str == NULL);
	n = read(fd, &c, 1);
	if (n == 0)
		return (free(buf), *str == NULL);
	if (c == '\n')
		return (free(buf), *str == NULL);
	if (n)
		buf[i++] = c;
	while (n && c != 0)
	{
		n = read(fd, &c, 1);
		if (c == '\n' && buf[i - 2] == '\n')
			break ;
		if (n != 0)
			buf[i] = c;
		i++;
	}
	return (buf[i - 1] = 0, buf[BUFSIZ - 1] = 0, *str = buf, 1);
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

void	err_msg(char *emsg)
{
	int	size;

	size = 0;
	while (emsg[size])
		size++;
	write (1, "Error\n", 7);
	write (1, emsg, size + 1);
	write (1, "\n", 1);
}
