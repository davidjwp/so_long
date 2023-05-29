/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:59:05 by djacobs           #+#    #+#             */
/*   Updated: 2023/05/29 13:59:06 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	get_height(char *str)
{
	int height;
	int	i;

	i = 0;
	height = 0;
	while (str[i] != 0)
		if (str[i++] == '\n')
			height++;
	return (height);
}

int	get_width(char *str)
{
	int	width;

	width = 0;
	while (str[i] != '\n')
		width++;
	return (width);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != 0)
		len++;
	return (len);
}
