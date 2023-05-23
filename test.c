#include "so_long.h"

typedef struct	s_img {
	void	*image;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct	s_xdata {
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}				t_xdata;

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000
#define	IMG_WIDTH 500
#define IMG_HEIGHT 500

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

int	PrintKey(int keysym, void *param)
{
	printf ("Keyrelease: %d\n", keysym);
	return (0);
}

int	CloseWin_Hook(int keysym, t_xdata mlx)
{
	if (keysym == XK_Escape)
	{
		PrintKey(keysym, &mlx);
		mlx_destroy_window(mlx.mlx_ptr, mlx.win_ptr);
	}
	return (0);
}

int	main(void)
{
	t_xdata	mlx;

	/*initialize mlx*/
	mlx.mlx_ptr = mlx_init();
	if (mlx.mlx_ptr == NULL)
		return (perror("Error mlx_init failed"), 0);

	/*create new image and get address data and get data for bpp, line_len and endian*/
	mlx.img.image = mlx_new_image(mlx.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	mlx.img.addr = mlx_get_data_addr(mlx.img.image, &mlx.img.bpp, \
	&mlx.img.line_len, &mlx.img.endian);

	/*create new window*/
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "new_window");
	if (mlx.win_ptr == NULL)
	{
		free(mlx.win_ptr);
		return (perror("Error new window"), 0);
	}

	/*key event hook for escaping the window*/
	// mlx_loop_hook(mlx.mlx_ptr, &LoopHook_NoEvent, &mlx);
	// mlx_key_hook(mlx.win_ptr, &CloseWin_Hook, &mlx);

	/*using mlx hook for different keypress*/
	mlx_hook(mlx.win_ptr, KeyPress, KeyPressMask, &CloseWin_Hook, &mlx);
	mlx_hook(mlx.win_ptr, KeyRelease, KeyReleaseMask, &PrintKey, &mlx);

	/*loop*/
	mlx_loop(mlx.mlx_ptr);
	mlx_destroy_display(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
	return (0);
}
