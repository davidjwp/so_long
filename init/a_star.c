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
void	fill_map_nodes(star_t *star, t_node ***node, char **map, t_pos p)
{
	while (map[p.y] != NULL)
	{
		while (map[p.y][p.x] != 0)
		{
			if (map[p.y][p.x] != 'P')
			{
				(*node)[p.y][p.x] = star->default_node;
				(*node)[p.y][p.x].x = p.x;
				(*node)[p.y][p.x].y = p.y;
				if (map[p.y][p.x] == '1')
					(*node)[p.y][p.x].wall = true;
			}
			p.x++;
		}
		(*node)[p.y][p.x] = NULL
		p.x = 0;
		p.y++;
	}
	(*node)[p.y] = NULL;
}


//size reference
int	update_node(t_node node, t_node **list, star_t star)
{
	int	i;

	i = 0;
	node.g = star->distance + 1;
	node.h = ((node.x - star->start_node.x) * -1) +\
	((node.y - star->start_node.y) * -1);
	node.f = node.h + node.g;
	while (i < 65)
		if (&(*list)[i++] == &node)
			if ((*list)[--i].g > node.g)
				return ((*list)[--i].g = node.g, 0);
	i = 0;
	while (i < 65 && &(*list)[i] != &node)
		if (&(*list)[i++] == &node)
			return (0);
	i = 0;
	while (&(*list)[i] != &star->default_node)
		i++;
	return ((*list)[i] = node, 0);
}

void	calc_neighbor(t_node ***map_nodes, t_pos pos, star_t *star)
{
	int	i;

	i = 0;
	if (*map_nodes[pos.y + 1][pos.x].wall == false &&\//up
	*map_nodes[pos.y + 1][pos.x].visited != true)
		update_node(*map_nodes[pos.y + 1][pos.x], &star->list, star);
	if (*map_nodes[pos.y - 1][pos.x].wall == false &&\//down
	*map_nodes[pos.y - 1][pos.x].visited != true)
		update_node(*map_nodes[pos.y - 1][pos.x], &star->list, star);
	if (*map_nodes[pos.y][pos.x + 1].wall == false &&\//right
	*map_nodes[pos.y][pos.x + 1].visited != true)
		update_node(*map_nodes[pos.y][pos.x + 1], &star->list, star);
	if (*map_nodes[pos.y][pos.x - 1].wall == false &&\//left
	*map_nodes[pos.y][pos.x - 1].visited != true)
		update_node(*map_nodes[pos.y][pos.x - 1], &star->list, star);
	while (&star->list[i] != &star->current_node)
		i++;
	star->list[i] = star->default_node;
}

bool	main_algo(star_t *star)
{
	int	distance;
	int	i;

	i = 0;
	distance = 0;
	while (star->list != NULL)
	{
		data->current_node = list[lowest_f(star->list, (t_pos){0, 0})];
		data->current_node.visited = true;
		distance++;
		if (&(star)->current_node == &(star)->end_node)
			return (true);
		else
			calc_neighbor(&star->map_nodes, (t_pos){star->current_node.y,\
			star->current_node.x});
		while (&star->list[i] == &star->default_node)
			if (i++ == 64)
				star->list = NULL;
	}
	return (false);
}

int	a_star(char	**map, star_t *star)
{
	t_pos	start;
	t_pos	end;
	int	i;

	i = 0;
	fill_map_nodes(star, &star->map_nodes, map, (t_pos){0, 0});
	while (i < 65)
		star->list[i] = star->default_node;
	end = get_pos(map, 'E', (t_pos){0, 0});
	star->end_node = star->map_nodes[pos.y][pox.x];
	start = get_pos(map, 'P', (t_pos){0,0});
	star->map_nodes[start.y][start.x].h = ((end.x - start.x) * -1) +\
	((end.y - start.y) * -1);
	star->map_nodes[start.y][start.x].g = 0;
	star->map_nodes[start.y][start.x].f = star->map_nodes[start.y][start.x].g +\
	star->map_nodes[start.y][start.x].h;
	star->start_node = star->map_nodes[start.y][start.x];
	star->list[0] = star->start_node;
	if (main_algo(star) == true)
		return (1);
	return (0);
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