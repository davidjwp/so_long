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

int	update_node(t_node node, t_list *list, star_t star)
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

void	calc_nodes(t_node **mnodes, t_list *lst, t_node *cnode, star_t star)
{
	if (mnodes[cnode->y + 1][cnode->x].wall == false &&\
	mnodes[cnode->y + 1][cnode->x].visited != true)
		update_node(mnodes[cnode->y + 1][cnode->x], lst, star);
	if (mnodes[cnode->y - 1][cnode->x].wall == false &&\
	mnodes[cnode->y - 1][cnode->x].visited != true)
		update_node(mnodes[cnode->y - 1][cnode->x], lst, star);
	if (mnodes[cnode->y][cnode->x + 1].wall == false &&\
	mnodes[cnode->y][cnode->x + 1].visited != true)
		update_node(mnodes[cnode->y][cnode->x + 1], lst, star);
	if (mnodes[cnode->y][cnode->x - 1].wall == false &&\
	mnodes[cnode->y][cnode->x - 1].visited != true)
		update_node(mnodes[cnode->y][cnode->x - 1], lst, star);
}

void	printcurrent(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp->node.visited != true)
		tmp = tmp->next;
	printf("(%i, %i)", tmp->node.x, tmp->node.y);
}

int	main_algo(t_node **map_node, t_pos start, t_pos end, star_t star)
{
	t_node	*currentnode;
	t_list	*list;

	list = NULL;
	add_list(&list, map_node[start.y][start.x]);
	while (list != NULL)
	{
		if (list == NULL)
			break;
		currentnode = find_lowestF(&list);
		currentnode->visited = true;
		printcurrent(list);
		map_node[currentnode->y][currentnode->x].visited = true;
		if (currentnode->x == end.x && currentnode->y == end.y)
			return (free_map(map_node, star), free_list(&list), 1);
		calc_nodes(map_node, list, currentnode, star);
		del_list(&list);
	}
	return (0);
}


t_node	**create_map(char **map, t_node **map_node, star_t star, t_node dflt)
{
	int	height;
	int	width;
 
	height = 0;
	width = 0;
	map_node = malloc(sizeof(t_node **) * star.mapWL.y);
	while (map[height] != NULL)
	{
		map_node[height] = malloc(sizeof(t_node) * star.mapWL.x);
		while (map[height][width] != 0)
		{
			map_node[height][width] = dflt;
			map_node[height][width].x = width;
			map_node[height][width].y = height;
			if (map[height][width] == '1')
				map_node[height][width].wall = true;
			width++;
		}
		height++;
		width = 0;
	}
	return (map_node);
}

int	a_star(char **map, star_t star)
{
	t_node	**map_node;
	t_pos	start;
	t_pos	end;

	write(1, "Path: ",6);
	map_node = create_map(map, map_node, star, (t_node){false, false, 0, 0,\
	INT_MAX, INT_MAX, INT_MAX});
	start = get_pos(map, 'P');
	end = get_pos(map, 'E');
	map_node[start.y][start.x].f = 0;
	map_node[start.y][start.x].g = 0;
	map_node[start.y][start.x].h = 0;
	if (main_algo(map_node, start, end, star))
		return (1);
	return (free_map(map_node, star), 0);
}

/*

1. Initialization:
   - Assign initial values to the start node, including `g` score, `h` score, and `f` score.
   - Calculate the heuristic estimate (`h` score) from each node to the end node based on their positions or any other available information.
   - Set the `g` score of the start node to 0, as it is the starting point.

2. Exploration:
   - Create an open set to store the discovered but not fully evaluated nodes.
   - Add the start node to the open set.
   - While the open set is not empty:
     - Select the node with the lowest `f` score from the open set as the current node.
     - If the current node is the end node, the algorithm terminates, and the path has been found.
     - Otherwise, for each neighboring node of the current node:
       - Calculate the `g` score of the neighboring node by adding the cost of moving from the current node to the neighboring node to the `g` score of the current node.
       - Calculate the heuristic estimate (`h` score) from the neighboring node to the end node.
       - Calculate the `f` score of the neighboring node by summing its `g` score and `h` score.
       - If the neighboring node is not in the open set, add it to the open set.
       - If the neighboring node is already in the open set and the new `g` score is lower than its previous `g` score, update the `g` score, `f` score, and parent pointer of the neighboring node.
     - Mark the current node as visited or remove it from the open set.

3. Path reconstruction:
   - If the algorithm terminates with the end node found, you can reconstruct the path from the end node to the start node by following the parent pointers from the end node back to the start node.

The A* algorithm uses the `f` score (combination of `g` and `h` scores) to guide the search towards the goal. The `h` score provides an estimated distance from each node to the end node based on heuristics, such as Euclidean distance or Manhattan distance.

In summary, your understanding is correct: The algorithm starts with an estimation of the distance (`h` score) from each node to the end node. By evaluating the `g` and `h` scores, the algorithm determines the most promising path based on the `f` score and explores neighboring nodes to progress towards the goal.

I hope this clarifies the steps involved in the A* algorithm. If you have any further questions, feel free to ask!*/