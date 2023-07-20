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

//size dependant
// void	fill_map_nodes(star_t star, t_node **node, char **map, t_pos p)
// {
// 	while (map[p.y] != NULL)
// 	{
// 		while (map[p.y][p.x] != 0)
// 		{
// 			if (map[p.y][p.x] != 'P')
// 			{
// 				node[p.y][p.x] = star.default_node;
// 				node[p.y][p.x].x = p.x;
// 				node[p.y][p.x].y = p.y;
// 				if (map[p.y][p.x] == '1')
// 					node[p.y][p.x].wall = true;
// 			}
// 			p.x++;
// 		}
// 		p.x = 0;
// 		p.y++;
// 	}
// }


// //size reference
// int	update_node(t_node node, t_node *list, star_t star)
// {
// 	int	i;

// 	i = 0;
// 	node.g = star.distance + 1;
// 	node.h = ((node.x - star.start_node.x) * -1) +\
// 	((node.y - star.start_node.y) * -1);
// 	node.f = node.h + node.g;
// 	while (i < 65)
// 		if (&list[i++] == &node)
// 			if (list[--i].g > node.g)
// 				return (list[--i].g = node.g, 0);
// 	i = 0;
// 	while (i < 65 && &list[i] != &node)
// 		if (&list[i++] == &node)
// 			return (0);
// 	i = 0;
// 	while (&list[i] != &star.default_node)
// 		i++;
// 	return (list[i] = node, 0);
// }

// void	calc_neighbor(t_node **map_nodes, t_pos pos, star_t star)
// {
// 	int	i;

// 	i = 0;
// 	if (map_nodes[pos.y + 1][pos.x].wall == false &&\
// 	map_nodes[pos.y + 1][pos.x].visited != true)
// 		update_node(map_nodes[pos.y + 1][pos.x], star.list, star);
// 	if (map_nodes[pos.y - 1][pos.x].wall == false &&\
// 	map_nodes[pos.y - 1][pos.x].visited != true)
// 		update_node(map_nodes[pos.y - 1][pos.x], star.list, star);
// 	if (map_nodes[pos.y][pos.x + 1].wall == false &&\
// 	map_nodes[pos.y][pos.x + 1].visited != true)
// 		update_node(map_nodes[pos.y][pos.x + 1], star.list, star);
// 	if (map_nodes[pos.y][pos.x - 1].wall == false &&\
// 	map_nodes[pos.y][pos.x - 1].visited != true)
// 		update_node(map_nodes[pos.y][pos.x - 1], star.list, star);
// 	while (&star.list[i] != &star.current_node)
// 		i++;
// 	star.list[i] = star.default_node;
// }

// int	main_algo(star_t star)
// {
// 	int	distance;

// 	distance = 0;
// 	while (!empty_list(star.list, star.default_node))
// 	{
// 		star.current_node = star.list[lowest_f(star.list, (t_pos){0, 0})];
// 		star.current_node.visited = true;
// 		distance++;
// 		if (&(star).current_node == &(star).end_node)
// 			return (true);
// 		else
// 			calc_neighbor(star.map_nodes, (t_pos){0, 0}, star);
// 	}
// 	return (false);
// }

// int	a_star(char **map)
// {
// 	star_t	star;
// 	t_pos	start;
// 	t_pos	end;
// 	int	i;

	
// 	star.default_node = (t_node){false, false, 0, 0, 0, INT_MAX, INT_MAX};
// 	star.current_node = (t_node){false, false, 0, 0, 0, INT_MAX, INT_MAX};
// 	i = 0;
// 	fill_map_nodes(star, star.map_nodes, map, (t_pos){0, 0});
// 	while (i < 65)
// 		star.list[i] = star.default_node;
// 	end = get_pos(map, 'E', (t_pos){0, 0});
// 	star.end_node = star.map_nodes[end.y][end.x];
// 	start = get_pos(map, 'P', (t_pos){0,0});
// 	star.map_nodes[start.y][start.x].h = ((end.x - start.x) * -1) +\
// 	((end.y - start.y) * -1);
// 	star.map_nodes[start.y][start.x].g = 0;
// 	star.map_nodes[start.y][start.x].f = star.map_nodes[start.y][start.x].g +\
// 	star.map_nodes[start.y][start.x].h;
// 	star.start_node = star.map_nodes[start.y][start.x];
// 	star.list[0] = star.start_node;
// 	if (main_algo(star) == true)
// 		return (1);
// 	return (0);
// }


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

int	print_list(t_list **list)
{
	t_list	*current;
	int	i;

	i = 0;
	current = *list;
	if (current == NULL)
		return (0);
	else if (current->next == NULL)
		return (printf("%i-{v:%i|x:%i|y:%i|f:%i|h:%i}\n", i++,\
		current->node.visited, current->node.x, current->node.y,\
		current->node.f, current->node.h), 0);
	while (current->next != NULL)
	{
		printf ("%i-{v:%i|x:%i|y:%i|f:%i|h:%i}\n", i++,\
		current->node.visited, current->node.x,	current->node.y,\
		current->node.f, current->node.h);
		current = current->next;
	}
	return (0);
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