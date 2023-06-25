#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define	NULL (void *)0
#define RIGHT_NODE	node[data->current_node.y][data->current_node.x + 1]
#define LEFT_NODE	node[data->current_node.y][data->current_node.x - 1]
#define UP_NODE		node[data->current_node.y + 1][data->current_node.x]
#define DOWN_NODE	node[data->current_node.y - 1][data->current_node.x]


typedef enum {
	true = 1,
	false = 0
}		bool;

//data AKA path struct 
typedef	struct s_xdata{
	int	map_len;
	int	map_width;
	int	y;
	int	x;
	t_node	default_node;
	t_node	end_node;
	t_node	current_node;
	t_node	start_node;
	int		distance;
}				t_xdata;

/*h is the approximate amount left to the end*/
/*g is the amount from start to current position*/
/*f is the sum of both g and h for the full path*/
typedef struct  s_node{
	bool	wall;
	bool    visited;
	int y;
	int x;
	int h;
	int g;
	int f;
}				t_node;

typedef struct	s_pos{
	int	x;
	int	y;
	int	g;
}				t_pos;

int	ft_strlen(char	**s, int y)
{
	int	i;

	i = 0;
	if (!y)
	{
		while (s[y][i])
			i++;
		return (i);
	}
	while (s[i])
		i++;
	return (i);
}

int	gnl(int fd, char **str)
{
	char	*buf;
	char	c;
	int		n;
	int		i;

	i = 0;
	buf = malloc(sizeof(char) * BUFSIZ);
	n = read(fd, &c, 1);
	if (c == '\n')
		return (free(buf), *str == NULL);
	if (n)
		buf[i++] = c;
	while (n && c != 0)
	{
		n = read(fd, &c, 1);
		if (c == '\n' && buf[i - 2] == '\n')
			break;
		if (n != 0)
			buf[i] = c;
		i++;
	}
	buf[i - 1] = 0;
	buf[BUFSIZ - 1] = 0;
	*str = buf;
	return (1);
}

static char	*ft_word_cpy(char const *s, char c)
{
	char	*word_cpy;
	int		word_len;
	int		index;

	index = 0;
	word_len = 0;
	while (s[word_len] != c && s[word_len])
		word_len++;
	word_cpy = (char *)malloc(word_len + 1);
	while (index < word_len)
	{
		word_cpy[index] = s[index];
		index++;
	}
	word_cpy[index] = '\0';
	return (word_cpy);
}

static int	ft_word_count(char const *s, char c)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!*s)
			return (word_count);
		word_count++;
		while (*s != c && *s)
			s++;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof (char *) * (ft_word_count(s, c) + 1));
	if (!split)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			split[index] = ft_word_cpy(s, c);
		index++;
		while (*s != c && *s)
			s++;
	}
	split[index - 1] = NULL;
	return (split);
}

void	get_node_values(t_xdata d, t_node ***nod, char **map)
{
	while (map[d.y] != 0)
	{
		while (map[d.y][d.x] != 0)
		{
			if (map[d.y][d.x] != 'P')
			{
				(*nod)[d.y][d.x] = d.default_node;
				(*nod)[d.y][d.x].x = d.x;
				(*nod)[d.y][d.x].y = d.y;
				if (map[d.y][d.x] == '1')
					(*nod)[d.y][d.x].wall = true;
			}
			else
			{
				(*nod)[d.y][d.x] = d.default_node;
				(*nod)[d.y][d.x].g = 0;
				(*nod)[d.y][d.x].f = (*nod)[d.y][d.x].g + (*nod)[d.y][d.x].h;
				(*nod)[d.y][d.x].x = d.x;
				(*nod)[d.y][d.x].y = d.y;
			}
		}
		d.x = 0;
		d.y++;
	}
}


int	lowest_f(t_node *list, t_pos pos)
{
	int	lowest_f;
	int	lowest_h;

	lowest_h = INT_MAX;
	lowest_f = list[pos.x].f;
	while (list[pos.x++].f != INT_MAX)
	{
		if (list[pos.x].f < lowest_f)
		{
			lowest_f = list[pos.x].f;
			pos.g = pos.x;
		}
	}
	pos.x = 0;
	while (list[pos.x].f != INT_MAX)
	{
		pos.x++;
		if (list[pos.x].f == lowest_f && pos.x != pos.g)
			if (list[pos.x].h < list[pos.g].h)
				lowest_h = list[pos.x].h;
	}
	if (lowest_h == INT_MAX)
		return (pos.g);
	return ()
}

int	lowest_f(t_node *list, t_pos pos)
{
	int	lowest_f;
	int	lowest_h;

	pos.g = pos.x;
	lowest_h = INT_MAX;
	lowest_f = list[pos.x].f;
	while (pos.y--)
	{
		while (list[pos.x++].f != INT_MAX)
		{
			if (list[pos.x].f < lowest_f && pos.x != pos.g)
			{
				lowest_f = list[pos.x].f;
				pos.g = pos.x;
			}
			else if (list[pos.x].f == lowest_f && pos.x != pos.g)
			{
				lowest_h = list[pos.x].h;
				pos.g = pos.x;
			}
		}
		pos.x = 0;
	}
	return (pos.g);
}

//size reference
int	update_node(t_node node, t_node **list, t_xdata *data)
{
	int	i;

	i = 0;
	node.g = data->distance + 1;
	node.h = ((node.x - data->start_node.x) * -1) +\
	((node.y - data->start_node.y) * -1);
	node.f = node.h + node.g;
	while (i < 64)
		if (&(*list)[i++] == &node)
			if ((*list)[--i].g > node.g)
				return ((*list)[--i].g = node.g, 0);
	if (&(*list)[i] == &node)
		return (0);
	i = 0;
	while ((*list)[i].f != INT_MAX)
		i++;
	return ((*list)[i] = node, 0);
}

void	calc_neighbor(t_node ***node, t_node **list, t_xdata *data)
{
	int	i;

	i = 0;
	if (LEFT_NODE->wall == false || LEFT_NODE->visited == true)
		update_node(*LEFT_NODE, list, data);
	if (UP_NODE->wall == false || UP_NODE->visited == true)
		update_node(*UP_NODE, list, data);
	if (DOWN_NODE->wall == false || DOWN_NODE->visited == true)
		update_node(*DOWN_NODE, list, data);
	if (RIGHT_NODE->wall == false || LEFT_NODE->visited == true)
		update_node(*RIGHT_NODE, list, data);
	while (&(*list)[i] != &data->current_node)
		i++;
	(*list)[i] = data->default_node;
}

bool	a_star(t_node *list, t_node **node, t_xdata *data)
{
	int	distance;

	distance = 0;
	while (&list != NULL)
	{
		data->current_node = list[lowest_f(list, (t_pos){0, 2, 0})];
		data->current_node.visited = true;
		distance++;
		if (&(data)->current_node == &(data)->end_node)
			return (true);
		else
			calc_neighbor(&node, &list, data);
	}
	return (false);
}

//size reference
int	main(int argc, char **argv)
{
	int	fd;
	char	*map;
	char	**map_split;
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
	node[y][x].h = ((i - node[y][x].x) * -1) + ((j - node[y][x].y) * -1);
	list[0] = node[y][x];
	data.start_node = node[y][x];
	data.current_node = node[y][x]; 

	if (a_star(list, node, &data) == true)
		return (printf("good path"), 0);
	return (printf("bad path"), 0);
}

/*Your understanding is mostly correct! Let me summarize the steps in the A* algorithm to clarify:

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