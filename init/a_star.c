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
			return (1);
		current = current->next;
	}
	if (!add_list(&list, node))
		return (0);
	return (1);
}

int	calc_nodes(t_node **mnodes, t_list *lst, t_node *cnode, t_star star)
{
	if (mnodes[cnode->y + 1][cnode->x].wall == FALSE && \
	mnodes[cnode->y + 1][cnode->x].visited != TRUE)
		if (!update_node(mnodes[cnode->y + 1][cnode->x], lst, star))
			return (err_msg("a_star add_list in update_node fail"), 0);
	if (mnodes[cnode->y - 1][cnode->x].wall == FALSE && \
	mnodes[cnode->y - 1][cnode->x].visited != TRUE)
		if (!update_node(mnodes[cnode->y - 1][cnode->x], lst, star))
			return (err_msg("a_star add_list in update_node fail"), 0);
	if (mnodes[cnode->y][cnode->x + 1].wall == FALSE && \
	mnodes[cnode->y][cnode->x + 1].visited != TRUE)
		if (!update_node(mnodes[cnode->y][cnode->x + 1], lst, star))
			return (err_msg("a_star add_list in update_node fail"), 0);
	if (mnodes[cnode->y][cnode->x - 1].wall == FALSE && \
	mnodes[cnode->y][cnode->x - 1].visited != TRUE)
		if (!update_node(mnodes[cnode->y][cnode->x - 1], lst, star))
			return (err_msg("a_star add_list in update_node fail"), 0);
	return (1);
}

int	main_algo(t_node **map_node, t_pos start, t_pos end, t_star star)
{
	t_node	*currentnode;
	t_list	*list;

	list = NULL;
	if (!add_list(&list, map_node[start.y][start.x]))
		return (err_msg("a_star add_list malloc fail"), 0);
	while (list != NULL)
	{
		if (list == NULL)
			break ;
		currentnode = find_lowestf(&list);
		currentnode->visited = TRUE;
		map_node[currentnode->y][currentnode->x].visited = TRUE;
		if (map_node[currentnode->y][currentnode->x].item == TRUE)
			star.items++;
		if (currentnode->x == end.x && currentnode->y == end.y)
			star.exit++;
		if (star.exit && star.items == star.dt_items)
			return (free_map_list(map_node, star, &list), 1);
		if (!calc_nodes(map_node, list, currentnode, star))
			return (free_map_list(map_node, star, &list), 0);
		del_list(&list);
	}
	return (free_map_list(map_node, star, &list), err_msg("blocked path"), 0);
}

t_node	**create_map(char **map, t_node **map_node, t_star star, t_node dflt)
{
	map_node = (t_node **)malloc(++star.mapwl.y * sizeof(t_node *));
	if (map_node == NULL)
		return (err_msg("map_node malloc fail"), map_node);
	while (map[dflt.y] != NULL)
	{
		map_node[dflt.y] = (t_node *)malloc(++star.mapwl.x * sizeof(t_node));
		if (map_node[dflt.y] == NULL)
			return (clean_map(map_node), map_node);
		while (map[dflt.y][dflt.x] != 0)
		{
			map_node[dflt.y][dflt.x] = dflt;
			if (map[dflt.y][dflt.x] == '1')
				map_node[dflt.y][dflt.x].wall = TRUE;
			else if (map[dflt.y][dflt.x] == 'C')
				map_node[dflt.y][dflt.x].item = TRUE;
			dflt.x++;
		}
		dflt.y++;
		dflt.x = 0;
	}
	return (map_node);
}

int	a_star(char **map, t_star star)
{
	t_node	**map_node;
	t_pos	start;
	t_pos	end;

	map_node = NULL;
	map_node = create_map(map, map_node, star, (t_node){FALSE, FALSE, FALSE, 0, \
	0, INT_MAX, INT_MAX, INT_MAX});
	if (map_node == NULL)
		return (err_msg("a_star malloc fail"), 0);
	start = get_pos(map, 'P');
	end = get_pos(map, 'E');
	map_node[start.y][start.x].f = 0;
	map_node[start.y][start.x].g = 0;
	map_node[start.y][start.x].h = 0;
	if (!main_algo(map_node, start, end, star))
		return (0);
	return (1);
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
