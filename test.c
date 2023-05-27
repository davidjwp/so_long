#include "so_long.h"

#define RED 0XFF0000
#define GREEN 0X00FF00
#define WHITE 0XFFFFFF
#define WIN_WIDTH 600
#define WIN_HEIGHT 300
#define	IMG_WIDTH WIN_WIDTH
#define IMG_HEIGHT WIN_HEIGHT

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

typedef struct s_rect{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;


int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

int	PrintKey(int keysym, void *param)
{
	printf ("Keyrelease: %d\n", keysym);
	return (0);
}

int	CloseWin_Hook(int keysym, t_xdata *mlx)
{
	if (keysym == XK_Escape)
	{
		PrintKey(keysym, &mlx);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx->win_ptr = NULL;
	}
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	img_pxl_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_rect(t_img *img, t_rect rect)
{
	int	i = rect.y;
	int	j;

	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pxl_put(img, j++, i, rect.color);
		i++;
	}
}

void	draw_background(t_img *img)
{
	int	i = 0;
	int j;

	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
			img_pxl_put(img, j++, i, WHITE);
		i++;
	}
}

int	render(t_xdata *mlx)
{
	if (mlx->win_ptr == NULL)
		return (0);	
	draw_background(&mlx->img);
	draw_rect(&mlx->img, (t_rect){WIN_WIDTH - 100, WIN_HEIGHT - 100,100,100,GREEN});
	draw_rect(&mlx->img, (t_rect){0,0,100,100,RED});

	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.image, 0,0);
	return (0);
}
/*don't forget to have the function for the hook be a pointer else it will mess up and segfault*/
/*make sure to draw the images IN the window so pay attention to the values given*/
int	main(void)
{
	t_xdata	mlx;


	/*initialize mlx*/
	mlx.mlx_ptr = mlx_init();
	if (mlx.mlx_ptr == NULL)
		return (perror("Error mlx_init failed"), 0);


	/*create new window*/
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "new_window");
	if (mlx.win_ptr == NULL)
	{
		free(mlx.win_ptr);
		return (perror("Error new window"), 0);
	}
	/*create new image and get address data and get data for bpp, line_len and endian*/
	mlx.img.image = mlx_new_image(mlx.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	mlx.img.addr = mlx_get_data_addr(mlx.img.image, &mlx.img.bpp, &mlx.img.line_len, &mlx.img.endian);
	/*key event hook for escaping the window*/
	// mlx_loop_hook(mlx.mlx_ptr, &LoopHook_NoEvent, &mlx);
	// mlx_key_hook(mlx.win_ptr, &CloseWin_Hook, &mlx);

	/*using mlx hook for different keypress*/
	mlx_loop_hook(mlx.mlx_ptr, &render, &mlx);
	mlx_hook(mlx.win_ptr, KeyPress, KeyPressMask, &CloseWin_Hook, &mlx);
	// mlx_hook(mlx.win_ptr, KeyRelease, KeyReleaseMask, &PrintKey, &mlx);

	/*loop*/
	mlx_loop(mlx.mlx_ptr);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img.image);
	mlx_destroy_display(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
	return (0);
}
