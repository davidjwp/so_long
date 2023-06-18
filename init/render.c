#include "../so_long.h"

void	render_walls(t_xdata *data, int walls, int x, int y)
{
	int	i;

	i = 0;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
	data->Ximg->background, x, y);
	while (i < walls)

}

void	render_background(t_xdata *data, int background, int x, int y)
{
	int	i;

	i = 0;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
	data->Ximg->background, x , y);
	while (i < background)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
		data->Ximg->background, x + IMG_HEIGHT, y + IMG_WIDTH);
		i++;
	}
}

void	render(t_xdata *data)
{
	char	**map_split;
	int	i;

	i = 0;
	map_split = ft_split(data->map.map, '\n');
	data->Ximg->background = mlx_xpm_file_to_image(data->mlx_ptr,\
	"xpm/background.xpm", IMG_WIDTH, IMG_HEIGHT);
	while (data->map.map[i])
	{
		if (data->map.map[i] == '1')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
			data->Ximg->wall, data->Ximg->pos.x, data->Ximg->pos.y);
		else if (data->map.map[i] == '0')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
			data->Ximg->background, data->Ximg->pos.x, data->Ximg->pos.y);
		else if (data->map.map[i] == 'C')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
			data->Ximg->character.img, data->Ximg->character.pos.x,\
			data->Ximg->character.pos.x);
		else if (data->map.map[i] == 'E')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
			data->Ximg->exit, data->Ximg->pos.x, data->Ximg->pos.y);
		data->Ximg->pos.x += IMG_HEIGHT;
		data->Ximg->pos.y += IMG_WIDTH;
	}
}
