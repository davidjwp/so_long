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

void	free_all_split(char **var)
{
	int i;

	i = 0;
	while (var[i] != NULL)
		free(var[i]);
	free(var);
}

int	gnl(char *str)
{
	char	buf;

	while (read())


}