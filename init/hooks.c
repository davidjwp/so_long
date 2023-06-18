#include "../so_long.h"

int	close_window(t_xdata *param)
{
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	mlx_loop_end(param->mlx_ptr);
	return (0);
}

int	controls(int keysym, t_xdata *param)
{
	if (keysym == XK_Escape)
		close_window(param);
	return (0);
}

