# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

#define WIN_WIDTH 500
#define WIN_HEIGHT 500	

typedef struct x_data{
	void	*mlx;
	void	*win;
}				t_xdata;

int	close_win(int keycode, t_xdata *data)
{
	mlx_loop_end(data->mlx);
}

int	main(int argc, char **argv)
{
	t_xdata	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "new_window");

	mlx_hook(data.win, DestroyNotify, 0L, close_win, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.win);
	mlx_destroy_window(data.mlx, data.win);
	return (0);
}