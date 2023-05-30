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
	int i;

	i = 0;
	while (var[i] != NULL)
		free(var[i]);
	free(var);
}

int	gnl(int fd, char **str)
{
	char	*buf;
	char	c;
	int	n;
	int	i;

	i = 0;
	buf = malloc(sizeof(char) * BUFSIZ);
	n = read(fd, &c, 1);
	while (n && c != 0)
	{
		n = read(fd, &c, 1);
		if (n != 0)
			buf[i] = c;
		i++;
	}
	buf[i] = 0;
	buf[BUFSIZ] = 0;
	*str = buf;
	return (1);
}