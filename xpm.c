#include "so_long.h"

#define WIDTH 740
#define HEIGHT 500

int    close_w(t_xdata *param)
{
    mlx_destroy_image(param->mlx_ptr, param->img_ptr);
    mlx_destroy_window(param->mlx_ptr, param->win_ptr);
}

int main(void)
{
    t_xdata data;
    int width;
    int height;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (perror("Error mlx_init failed"), 0);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "new_window");
	if (data.win_ptr == NULL)
		return (free(data.win_ptr), perror("Error new window"), 0);
	data.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
    data.img_ptr = mlx_xpm_file_to_image(data.mlx_ptr, "Untitled.xpm", &width, &height);
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0,0);
    mlx_hook(data.win_ptr, DestroyNotify, 0L, &close_w, &data);
	mlx_loop(data.mlx_ptr);
    return (0);
}