int	ft_put_circle(t_xdata mlx, t_pos centre, int radius, int color)
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
	return (0);
}

void	DrawLine(t_xdata mlx, t_points points)
{
	while (points.p1x != points.p2x && points.p1y != points.p2y)
	{
		if (points.p1x < points.p2x)
			points.p1x++;
		else
			points.p1x--;
		if (points.p1y < points.p2y)
			points.p1y++;
			else
		points.p1y--;
		mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, points.p1x, points.p1y, 0X00FF00);
	}
}
