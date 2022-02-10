#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx_opengl_20191021/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"

# define RESOULTION	 	900
# define SCALE_MAX		50000000
# define IRIS			1.42

# define WHEEL_UP		0x04
# define WHEEL_DOWN		0x05
# define Q				12
# define E				14
# define W				13
# define A				0
# define S				1
# define D				2
# define UP				126
# define LEFT			123
# define DOWN			125
# define RIGHT			124
# define ESC 			53

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_mlx;

typedef struct s_fractol
{
	t_mlx	mlx;
	int		r_rgb;
	int		g_rgb;
	int		b_rgb;
	int		(*blueprint)(struct s_fractol *, double, double);
	int		iter_max;
	double	scale;
	double	xr;
	double	yi;
	double	cr;
	double	ci;
}				t_fractol;

void	draw_fractal(t_fractol *f);
int		zoom_in(int x, int y, t_fractol *f);
int		zoom_out(int x, int y, t_fractol *f);
int		wheel(int input, int x, int y, t_fractol *f);
int		press(int input, t_fractol *f);
char	*f2a(double f);
double	a2f(char *str);
int		julia(t_fractol *f, double a, double b);
int		mandelbrot(t_fractol *f, double a, double b);
int		bonus(t_fractol *f, double a, double b);

#endif
