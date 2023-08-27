/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:09:20 by djacobs           #+#    #+#             */
/*   Updated: 2023/06/29 12:09:21 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	update_node(t_node node, t_list *list, t_star star)
{
	t_list	*current;

	current = list;
	node.g = star.distance + 1;
	node.h = ((node.x - star.start.x) * -1) + ((node.y - star.start.y) * -1);
	node.f = node.h + node.g;
	while (current != NULL)
	{
		if (current->node.x == node.x && current->node.y == node.y)
			return (0);
		current = current->next;
	}
	return (add_list(&list, node), 0);
}

void	calc_nodes(t_node **mnodes, t_list *lst, t_node *cnode, t_star star)
{
	if (mnodes[cnode->y + 1][cnode->x].wall == FALSE && \
	mnodes[cnode->y + 1][cnode->x].visited != TRUE)
		update_node(mnodes[cnode->y + 1][cnode->x], lst, star);
	if (mnodes[cnode->y - 1][cnode->x].wall == FALSE && \
	mnodes[cnode->y - 1][cnode->x].visited != TRUE)
		update_node(mnodes[cnode->y - 1][cnode->x], lst, star);
	if (mnodes[cnode->y][cnode->x + 1].wall == FALSE && \
	mnodes[cnode->y][cnode->x + 1].visited != TRUE)
		update_node(mnodes[cnode->y][cnode->x + 1], lst, star);
	if (mnodes[cnode->y][cnode->x - 1].wall == FALSE && \
	mnodes[cnode->y][cnode->x - 1].visited != TRUE)
		update_node(mnodes[cnode->y][cnode->x - 1], lst, star);
}

int	main_algo(t_node **map_node, t_pos start, t_pos end, t_star star)
{
	t_node	*currentnode;
	t_list	*list;

	list = NULL;
	add_list(&list, map_node[start.y][start.x]);
	while (list != NULL)
	{
		if (list == NULL)
			break ;
		currentnode = find_lowestf(&list);
		currentnode->visited = TRUE;
		map_node[currentnode->y][currentnode->x].visited = TRUE;
		if (currentnode->x == end.x && currentnode->y == end.y)
			return (free_map_list(map_node, star, &list), 1);
		calc_nodes(map_node, list, currentnode, star);
		del_list(&list);
	}
	return (free_map_list(map_node, star, &list), 0);
}

t_node	**create_map(char **map, t_node **map_node, t_star star, t_node dflt)
{
	int	height;
	int	width;

	height = 0;
	width = 0;
	map_node = (t_node **)malloc(++star.mapwl.y * sizeof(t_node *));
	while (map[height] != NULL)
	{
		map_node[height] = (t_node *)malloc(++star.mapwl.x * sizeof(t_node));
		while (map[height][width] != 0)
		{
			map_node[height][width] = dflt;
			map_node[height][width].x = width;
			map_node[height][width].y = height;
			if (map[height][width] == '1')
				map_node[height][width].wall = TRUE;
			width++;
		}
		height++;
		width = 0;
	}
	return (map_node);
}

int	a_star(char **map, t_star star)
{
	t_node	**map_node;
	t_pos	start;
	t_pos	end;

	map_node = NULL;
	map_node = create_map(map, map_node, star, (t_node){FALSE, FALSE, 0, 0, \
	INT_MAX, INT_MAX, INT_MAX});
	start = get_pos(map, 'P');
	end = get_pos(map, 'E');
	map_node[start.y][start.x].f = 0;
	map_node[start.y][start.x].g = 0;
	map_node[start.y][start.x].h = 0;
	if (main_algo(map_node, start, end, star))
		return (1);
	return (0);
}

/*
* The A star algorithm works like this.
*
* 1. Initialization:
*	- I create a 2d map of the real map made of nodes
*	- Each node contains 'g' score, 'h' score and 'f' score
*	- The 'g' score is the approximate value from current position to start
*	- The 'h' score is the heuristic value, i.e the approximate value from
*	start to finish using a Manhattan distance algorithm
*	- The 'f' score the sum of both
*	- the values are all initialized in create_map
*
* 2. Exploration:
*	- I create a list of the discovered nodes, meaning the nodes that are around
*	the current node
*	- The list is for all the nodes that can i can move to
*	- When i move to the an open node i remove it from the list
*	- Each time a node is added to the list i update it's values
*	- I decide which node to move to by looking through the list and checking
*	for the smallest 'f' score, if the scores are the same i look for the
*	smallest 'h' score
*
* 3. Path reconstruction:
*	- Eventually every node available to be discovered is explored, and if the
*	end node is not found then there is an error and i exit the algorithm
*
*/
