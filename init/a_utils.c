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

t_node	*find_lowestf(t_list **list)
{
	t_node	*lowestfnode;
	t_list	*current;
	int		lowesth;

	lowestfnode = &(*list)->node;
	current = *list;
	while (current != NULL)
	{
		if (current->node.f < lowestfnode->f)
			lowestfnode = &current->node;
		current = current->next;
	}
	current = *list;
	lowesth = INT_MAX;
	while (current != NULL)
	{
		if (current->node.f == lowestfnode->f && current->node.h < lowesth)
		{
			lowestfnode = &current->node;
			lowesth = lowestfnode->h;
		}
		current = current->next;
	}
	return (lowestfnode);
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

	newlnode = malloc(sizeof(t_list));
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
	if (head->node.visited == TRUE)
	{
		link = (*list)->next;
		free(*list);
		*list = link;
	}
	else
	{
		while (head->next->node.visited != TRUE && head->next->next != NULL)
			head = head->next;
		if (head->next->next != NULL)
			link = head->next->next;
		free(head->next);
		head->next = link;
	}
}

int	free_map_list(t_node **map_node, t_star star, t_list **list)
{
	t_list	*mv;
	int		y;

	y = 0;
	while (star.mapwl.y--)
	{
		free(map_node[y]);
		y++;
	}
	free(map_node);
	if (*list == NULL)
		return (0);
	while ((*list)->next != NULL)
	{
		mv = (*list)->next;
		free(*list);
		*list = mv;
	}
	return (free(*list), 0);
}
