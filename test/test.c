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

typedef struct s_pos{
	int x;
	int y;
}			t_pos;

typedef struct	s_xdata {
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_pos	position;
	int		KeyArray[16];
}				t_xdata;


typedef struct s_rect{
	t_pos position;
	int width;
	int height;
	int color;
}	t_rect;


int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

int	PrintKey(int keysym)
{
	printf ("Keyrelease: %d\n", keysym);
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
	int	i = rect.position.y;
	int	j;

	while (i < rect.position.y + rect.height)
	{
		j = rect.position.x;
		while (j < rect.position.x + rect.width)
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

int	controls(int keysym, t_xdata *mlx)
{
	if (keysym == XK_w && mlx->position.y >= 1)
		mlx->position.y -= 10;
	else if (keysym == XK_d && mlx->position.x <= IMG_WIDTH - 110)
		mlx->position.x += 10;
	else if (keysym == XK_a && mlx->position.x >= 1)
		mlx->position.x -= 10;
	else if (keysym == XK_s && mlx->position.y <= IMG_HEIGHT - 110)
		mlx->position.y += 10;
	if (keysym == XK_Escape){
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx->win_ptr = NULL;
		mlx_loop_end(mlx->mlx_ptr);
	}
	// PrintKey(keysym);
	return (0);
}

int close_my_window(t_xdata *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->win_ptr = NULL;
	mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

int	render(t_xdata *mlx)
{
	if (mlx->win_ptr == NULL)
		return (0);	
	draw_background(&mlx->img);
	draw_rect(&mlx->img, (t_rect){mlx->position.x, mlx->position.y,100,100,GREEN});
	// draw_rect(&mlx->img, (t_rect){0,0,100,100,RED});

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
	mlx_hook(mlx.win_ptr, DestroyNotify, 0L, &close_my_window, &mlx);
	mlx_hook(mlx.win_ptr, KeyPress, KeyPressMask, &controls, &mlx);
	// mlx_hook(mlx.win_ptr, KeyPress, KeyPressMask, &controls, &mlx);
	// mlx_hook(mlx.win_ptr, KeyRelease, KeyReleaseMask, &PrintKey, &mlx);

	/*loop*/
	mlx_loop(mlx.mlx_ptr);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img.image);
	mlx_destroy_display(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
	return (0);
}

// #include <mlx.h>
// #include <X11/keysym.h>

// typedef struct s_xdata{
// 	void	*mlx;
// 	void	*win;
// }	t_xdata;

// int	CloseWindow(int event, t_xdata *data)
// {
// 	// mlx_hook(data->win, 33, 1L<<17, (void *)0, (void *)0);
// 	mlx_destroy_window(data->mlx, data->win);
// 	return(0);
// }

// int CloseWindowKey(int keycode, t_xdata *data)
// {
// 	if (keycode == XK_Escape){
// 		mlx_destroy_window(data->mlx, data->win);
// 		mlx_loop_end(data->mlx);
// 	}
// 	return (0);
// }

// int	main(void)
// {
// 	t_xdata	data;

// 	data.mlx = mlx_init();
// 	data.win = mlx_new_window(data.mlx, 400, 250, "window");
// 	mlx_hook(data.win, 3, 1L<<1, &CloseWindowKey, &data);
// 	mlx_hook(data.win, 33, 1L<<17, &CloseWindow, &data);
// 	mlx_loop(data.mlx);
// 	return (0);
// }
