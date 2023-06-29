/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:04:51 by djacobs           #+#    #+#             */
/*   Updated: 2023/06/29 12:04:52 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	a_star(char **map, a)
{
	t_node	node[63][64];
	t_node	list[64];
	t_xdata	data;
	int	i;
	int	j;
	int	x;
	int	y;

	open(argv[1], fd);
	gnl(fd, &map);
	map_split = ft_split(map, '\n');

	//fill list to avoid errors
	int	w;

	w = 0;
	while (w < 64)
		list[w] = data.default_node;

	i = 0;
	j = 0;
	while (map_split[j][i] != 'E')
	{
		if (!map_split[j][i++])
		{
			i = 0;
			j++;
		}
	}
	data.end_node = node[j][i];
	data = (t_xdata){ft_strlen(map_split, 0), ft_strlen(map_split, 1)\
	, 0, 0, (t_node){false, false, 0, 0, 0, INT_MAX, INT_MAX}};
	get_node_values(data, &node, map_split);

	while(node[y][x].g != 0)
	{
		if (x++ >= 64)
		{
			x = 0;
			y++;
		}
	}
	fill_list(list, &data);
	node[y][x].h = ((i - node[y][x].x) * -1) + ((j - node[y][x].y) * -1);
	list[0] = node[y][x];
	data.start_node = node[y][x];
	data.current_node = node[y][x]; 

	if (a_star(list, node, &data) == true)
		return (printf("good path"), 0);
	return (printf("bad path"), 0);
}
