#include "../includes/fractol.h"

int	julia(t_fractol *f, double a, double b)
{
	int		depth;
	double	zr;
	double	zi;
	double	next_zr;

	depth = 0;
	zr = a + f->xr;
	zi = b + f->yi;
	if (f->cr == 0 && f->ci == 0)
	{
		f->cr = -0.79;
		f->ci = 0.15;
	}
	while ((zr * zr) + (zi * zi) < 4 && depth < f->iter_max)
	{
		next_zr = (zr * zr) - (zi * zi) + f->cr;
		zi = (2 * zi * zr) + f->ci;
		zr = next_zr;
		depth += 1;
	}
	return (depth);
}

int	mandelbrot(t_fractol *f, double a, double b)
{
	int		depth;
	double	zr;
	double	zi;
	double	next_zr;

	depth = 0;
	zr = 0;
	zi = 0;
	f->cr = a + f->xr;
	f->ci = b + f->yi;
	while ((zr * zr) + (zi * zi) < 4 && depth < f->iter_max)
	{
		next_zr = (zr * zr) - (zi * zi) + f->cr;
		zi = (2 * zi * zr) + f->ci;
		zr = next_zr;
		depth += 1;
	}
	return (depth);
}

int	bonus(t_fractol *f, double a, double b)
{
	int		depth;
	double	zr;
	double	zi;
	double	next_zr;

	depth = 0;
	zr = a + f->xr;
	zi = b + f->yi;
	f->cr = 0.28;
	f->ci = 0.008;
	while ((zr * zr) + (zi * zi) < 4 && depth < f->iter_max)
	{
		next_zr = (zr * zr) - (zi * zi) + f->cr;
		zi = (2 * zi * zr) + f->ci;
		zr = next_zr;
		depth += 1;
	}
	return (depth);
}

void	draw_fractal(t_fractol *f)
{
	int		depth;
	int		rgb_xy;
	int		y;
	int		x;

	y = -1;
	while (++y < RESOULTION)
	{
		x = -1;
		while (++x < RESOULTION)
		{
			depth = f->blueprint(f, (x / f->scale), (y / f->scale));
			rgb_xy = (y * f->mlx.size_line) + (x * (f->mlx.bpp / 8));
			f->mlx.addr[rgb_xy] = f->b_rgb + (depth * 3.8);
			f->mlx.addr[rgb_xy + 1] = f->g_rgb + (depth * 2.2);
			f->mlx.addr[rgb_xy + 2] = f->r_rgb + (depth * 5.2);
		}
	}
	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img, 0, 0);
}
