#include "../includes/fractol.h"

int	zoom_in(int x, int y, t_fractol *f)
{
	double	scale_multi;

	if (f->scale >= SCALE_MAX)
		return (0);
	scale_multi = f->scale * IRIS;
	f->xr = ((double)x / f->scale + f->xr) - ((double)x / scale_multi);
	f->yi = ((double)y / f->scale + f->yi) - ((double)y / scale_multi);
	f->scale *= IRIS;
	return (1);
}

int	zoom_out(int x, int y, t_fractol *f)
{
	double	scale_multi;

	if (f->scale <= RESOULTION / 6)
		return (0);
	scale_multi = f->scale / IRIS;
	f->xr = ((double)x / f->scale + f->xr) - ((double)x / scale_multi);
	f->yi = ((double)y / f->scale + f->yi) - ((double)y / scale_multi);
	f->scale /= IRIS;
	return (1);
}

int	wheel(int input, int x, int y, t_fractol *f)
{
	if (input == WHEEL_UP)
	{
		if (!zoom_out(x, y, f))
			return (0);
	}
	else if (input == WHEEL_DOWN)
	{
		if (!zoom_in(x, y, f))
			return (0);
	}
	else
		return (0);
	draw_fractal(f);
	return (0);
}

int	press(int input, t_fractol *f)
{
	if (input == Q)
		f->r_rgb -= 42;
	else if (input == E)
		f->r_rgb += 42;
	else if (input == W || input == UP)
		f->yi -= 20 / f->scale;
	else if (input == S || input == DOWN)
		f->yi += 20 / f->scale;
	else if (input == A || input == LEFT)
		f->xr -= 20 / f->scale;
	else if (input == D || input == RIGHT)
		f->xr += 20 / f->scale;
	else if (input == ESC)
		exit(0);
	else
		return (0);
	draw_fractal(f);
	return (0);
}
