#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


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

void	get_node_values(t_node ***node, char **map, t_node default, t_pos pos)
{
	while (map[y] != 0)
	{
		while (map[y][x] != 0)
		{
			if (map[y][x] != 'P')
			{
				(*node)[y][x] = default;
				(*node)[y][x].x = x;
				(*node)[y][x].y = y;
				if (map[y][x] == '1')
					(*node)[y][x].wall = true;
			}
			else
			{
				(*node)[y][x] = default;
				(*node)[y][x].g = 0;
				(*node)[y][x].h = 10;			//approximate using length of the map
				(*node)[y][x].f = (*node)[y][x].g + (*node)[y][x].h;
				(*node)[y][x].x = x;
				(*node)[y][x].y = y;
			}
		}
		x = 0;
		y++;
	}
}

int	a_star(t_node ***node, char **map)
{
	t_pos	pos;
	bool	path;

	path = false;
	while (path == false)
	{
		while (map[y][x] != 0)
		{
			
		}
	}
}

int	main(int argc, char **argv)
{
	int	fd;
	char	*map;
	char	**map_split;
	t_node	node[63][64];

	open(argv[1], fd);
	gnl(fd, &map);
	map_split = ft_split(map, '\n');

	get_node_values(&node, map_split, (t_node){false, false, 0, 0, 0, INT_MAX,\
	INT_MAX}, (t_pos){0, 0, 0});

	a_star(&node, map_split);
	return (0);
}
