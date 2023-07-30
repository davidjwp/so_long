/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:28:25 by djacobs           #+#    #+#             */
/*   Updated: 2023/06/29 13:28:27 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// int	lowest_h(t_node *list, t_pos pos, int Flow, int	Hlow)
// {
// 	int	i;

// 	i = 0;
// 	pos.x = INT_MAX;
// 	while (i != pos.y)
// 	{
// 		if (list[i].f == Flow && i != pos.y)
// 		{
// 			if (list[i].h < Hlow)
// 			{
// 				Hlow = list[pos.x].h;
// 				pos.x = i;
// 			}
// 		}
// 		i++;
// 	}
// 	return (pos.x);
// }

// int	lowest_f(t_node *list, t_pos pos)
// {
// 	int	Flow;
// 	int	Hlow;

// 	Hlow = INT_MAX;
// 	Flow = list[pos.x].f;
// 	while (list[pos.x++].f != INT_MAX)
// 	{
// 		if (list[pos.x].f <= Flow)
// 		{
// 			Flow = list[pos.x].f;
// 			pos.y = pos.x;
// 		}
// 	}
// 	Hlow = lowest_h(list, pos, Flow, Hlow);
// 	if (Hlow == INT_MAX)
// 		return (pos.y);
// 	return (Hlow);
// }

// t_pos	get_pos(char **map, char c, t_pos pos)
// {
// 	while (map[pos.y][pos.x] != c)
// 	{
// 		if (!map[pos.y])
// 		{
// 			pos.x = 0;
// 			pos.y++;
// 		}
// 		pos.x++;
// 	}
// 	return (pos);
// }

// int	empty_list(t_node *list, t_node default_node)
// {
// 	int	i;

// 	i = 0;
// 	while (&list[i] == &default_node && i < 65)
// 		i++;
// 	if (i == 64)
// 		return (true);
// 	return (false);
// }

t_node	*find_lowestF(t_list **list)
{
	t_node	*lowestFnode;
	t_list	*current;
	int	lowestH;

	lowestFnode = &(*list)->node;
	current = *list;
	while (current != NULL)
	{
		if (current->node.f < lowestFnode->f)
			lowestFnode = &current->node;
		current = current->next;
	}
	current = *list;
	lowestH = INT_MAX;
	while (current != NULL)
	{
		if (current->node.f == lowestFnode->f && current->node.h < lowestH)
		{
			lowestFnode = &current->node;
			lowestH = lowestFnode->h;
		}
		current = current->next;
	}
	return (lowestFnode);
}

t_pos	get_pos(char **map, char c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y] != NULL)
	{
		while (map[y][x] != 0)
		{
			if (map[y][x] == c)
				return ((t_pos){y, x});
			x++;
		}
		y++;
		x = 0;
	}
	return ((t_pos){0, 0});
}

void	add_list(t_list **list, t_node newnode)
{
	t_list	*newlnode;
	t_list	*tmp;

	newlnode = (t_list *)malloc(sizeof(t_list));
	newlnode->node = newnode;
	newlnode->next = NULL;
	if (*list == NULL)
		*list = newlnode;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newlnode;
	}
}

void	del_list(t_list **list)
{
	t_list	*head;
	t_list	*link;

	link = NULL;
	head = *list;
	if (head->node.visited == true)
	{
		link = (*list)->next;
		free(*list);
		*list = link;
	}
	else
	{
		while (head->next->node.visited != true && head->next->next != NULL)
			head = head->next;
		if (head->next->next != NULL)
			link = head->next->next;
		free(head->next);
		head->next = link;
	}
}

void	free_map(t_node **map_node, star_t star)
{
	int	i;

	i = 0;
	while (star.mapWL.y)
	{
		free(map_node[i]);
		star.mapWL.y--;
		i++;
	}
	free(map_node);
}

void	free_list(t_list **list)
{
	while ((*list)->next != NULL)
	{
		free(*list);
		*list = (*list)->next;
	}
}
