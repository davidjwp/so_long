#include "so_long.h"
#include <math.h>

typedef struct	s_xdata {
	void	*mlx_ptr;
	void	*win_ptr;
}				t_xdata;

// typedef struct	s_data {
	// void	*img;
	// char	*addr;
	// int		bits_per_pixel;
	// int		line_length;
	// int		endian;
// }				t_data;

typedef struct	s_pos {
	int	x;
	int	y;
}				t_pos;
#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000
#define	IMG_WIDTH 600
#define IMG_HEIGHT 500

void	ft_put_circle(t_xdata mlx, t_pos centre, int radius, int color)
{
	float x = 0.0, y = 0.0;
	double theta = 0.0;

	while (theta <= (2 * 3.14159265))
	{
		x= centre.x + radius * cos(theta);
		y= centre.y + radius * sin(theta);
		mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, (int)x, (int)y, color);
		theta += 0.0005;
	}
}

void	close_win_event(t_xdata mlx)
{
	mlx_destroy_window(mlx.mlx_ptr, mlx.win_ptr);
	if (mlx.win_ptr)
	{
		perror("Error closign window");
		exit(0);
	}
	exit(1);
}
// 
// int	main(void)
// {
	// t_xdata	mlx;
	// t_data	img;
	// t_pos centre;
	// centre.x = 500;
	// centre.y = 500;
	// void	(*circle)(t_xdata, t_pos, int, int) = &ft_put_circle; 
	// void	(*close_win)(t_xdata) = &close_win_event;
// 
	// /*initialize mlx*/
	// mlx.mlx_ptr = mlx_init();
	// if (mlx.mlx_ptr == NULL)
		// return (perror("Error mlx_init failed"), 0);
// 
	// /*create new image and get address data for that image so you can manipulate the image from the data*/
	// img.img = mlx_new_image(mlx.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 
	// /*create new window*/
	// mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "new_window");
	// if (mlx.win_ptr == NULL)
	// {
		// free(mlx.win_ptr);
		// return (perror("Error new window"), 0);
	// }
	// 
	// /*draw circle*/
	// for(int i = 0; i < 10; i++)
		// (*circle)(mlx, centre, 20+i, 0X00FF00);
	// if (mlx.win_ptr == NULL)
		// return (free(mlx.mlx_ptr), perror("Error mlx_new_window failed"), 0);
	// (*close_win)(mlx);
// 
	// mlx_loop_hook();
	// /*loop*/
	// mlx_loop(mlx.mlx_ptr);
	// free(mlx.mlx_ptr);
	// return (0);
// }

#include <X11/keysym.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int	handle_no_event(void *data)
{
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}


int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (0);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (0);
	}

	/* Setup hooks */ 
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_key_hook(data.win_ptr, &handle_input, &data);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
