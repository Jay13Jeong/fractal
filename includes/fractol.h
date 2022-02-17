#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"

# define RESOULTION	 	900 //가로세로 각각의 길이
# define SCALE_MAX		50000000 //최대 확대 선명도
# define IRIS			1.42 //축소, 확대 배율

/*애플키보드 키코드 매크로 */
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

typedef struct s_mlx //mlx구조체
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
	int		r_rgb; //red값
	int		g_rgb; //green값
	int		b_rgb; //blue값
	int		(*blueprint)(struct s_fractol *, double, double); //프렉탈 설계함수 포인터
	int		iter_max; //무한등비급수의 최대 n
	double	scale; //해상도를 가로세로 4:4비율(x:-2~2, y:-2~2)로 했을 때 출력규모
	double	xr; //Z(n + 1)의 실수부분
	double	yi;	//Z(n + 1)의 허수부분
	double	cr;	//복소수 실수부분
	double	ci;	//복소수 허수부분
}				t_fractol;

void	draw_fractal(t_fractol *f);
int		zoom_in(int x, int y, t_fractol *f);
int		zoom_out(int x, int y, t_fractol *f);
int		wheel(int input, int x, int y, t_fractol *f);
int		press(int input, t_fractol *f);
double	a2f(char *str);
int		julia(t_fractol *f, double a, double b);
int		mandelbrot(t_fractol *f, double a, double b);
int		bonus(t_fractol *f, double a, double b);

#endif
