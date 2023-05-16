#include "so_long.h"
#include <math.h>

typedef struct	s_xdata {
	void	*mlx_ptr;
	void	*win_ptr;
}				t_xdata;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_pos {
	int	x;
	int	y;
}				t_pos;
#define WIN_WIDTH 1500
#define WIN_HEIGHT 1500
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

int	main(void)
{
	t_xdata	mlx;
	t_data	img;
	t_pos centre;
	centre.x = 750;
	centre.y = 750;
	void	(*circle)(t_xdata, t_pos, int, int) = &ft_put_circle; 

	mlx.mlx_ptr = mlx_init();
	if (mlx.mlx_ptr == NULL)
		return (perror("Error mlx_init failed"), 0);
	img.img = mlx_new_image(mlx.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "new_window");
	if (mlx.win_ptr == NULL)
		return (free(mlx.mlx_ptr), perror("Error mlx_new_window failed"), 0);
	mlx_loop(mlx.mlx_ptr);
	mlx_destroy_window(mlx.mlx_ptr, mlx.win_ptr);
	free(mlx.mlx_ptr);
	return (0);
}
