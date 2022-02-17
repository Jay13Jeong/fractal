#include "../includes/fractol.h"

/*
f(Z(n)) = Z(n+1) = (Z(n))^2 + C
Z(n) = a + bi, c = cr + ci
f(Z(n)) = a^2 - b^2 + cr + (2ab + ci)
zr = a^2 - b^2 + cr (등비수열 실수부분)
zi = 2ab + ci		(등비수열 허수부분)
위 식은 무하루프를 돌 수 있기떄문에 두가지 종료조건 필요함
| a^2 - b^2 + cr | > 4
1. 4를 넘어가면 스케일에서 벗어나므로 그릴수 없음
2. 인자로 받아온 max값까지만 등비수열을 진행한다.
*/

//줄리아 설계도 함수
int	julia(t_fractol *f, double a, double b)
{
	int		depth; //등비수열 n
	double	zr; //등비수열 식의 실수부분
	double	zi;	//등비수열 식의 허수부분
	double	next_zr; //다음n+1번째 등비수열 식의 실수부분

	depth = 0;
	zr = a + f->xr;
	zi = b + f->yi;
	if (f->cr == 0 && f->ci == 0)
	{
		f->cr = -0.79; /*특별히 설정된 값이없으면 설정되는 복소수 기본값 */
		f->ci = 0.15;
	}
	while ((zr * zr) + (zi * zi) < 4 && depth < f->iter_max) //종료조건
	{
		next_zr = (zr * zr) - (zi * zi) + f->cr;
		zi = (2 * zi * zr) + f->ci;
		zr = next_zr;
		depth += 1;
	}
	return (depth);
}

//망델브로 설계도 함수
int	mandelbrot(t_fractol *f, double a, double b)
{
	int		depth;
	double	zr;
	double	zi;
	double	next_zr;

	depth = 0;
	zr = 0; /*이 등비수열은 줄리아의 z와 c의 역할을 바꾸면 망델브로가 된다 */
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

//추가 프렉탈(줄리아 파생)
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

//구조체에 설정된 설계도로 프렉탈을 mlx에 그리는 함수 
void	draw_fractal(t_fractol *f)
{
	int		depth; //등비수열의 마지막n, 수열이 끝이 안보일수록 다른 색상으로 표현됨 (rgb값에 더할 값)
	int		rgb_xy; //int형이 4바이트여서 rgb 각 색상코드(4바이트)가 딱들어감
	int		y;
	int		x;

	y = -1;
	while (++y < RESOULTION)
	{
		x = -1;
		while (++x < RESOULTION)
		{
			depth = f->blueprint(f, (x / f->scale), (y / f->scale)); //설정된 설계도로 등비수열 진행후, 마지막 n값을 가져온다.
			rgb_xy = (y * f->mlx.size_line) + (x * (f->mlx.bpp / 8)); //mlx의 화면의 전체픽셀중 세로(y * 실제 할당된 가로사이즈), 가로(x * 비트당 픽셀/8)씩 이동하면서 채움(픽셀 하나당 4바이트)
			f->mlx.addr[rgb_xy] = f->b_rgb + (depth * 3.8); //화려하게 표현하기 위해 파란색의 수치를 3.8(무작위 수)만큼 변형해서 현재 픽셀에 섞기
			f->mlx.addr[rgb_xy + 1] = f->g_rgb + (depth * 2.2); //현재픽셀에 같은방식으로 초록색 섞기
			f->mlx.addr[rgb_xy + 2] = f->r_rgb + (depth * 5.2); //현재픽셀에 같은방식으로 붉은색 섞기
		}
	}
	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img, 0, 0); //완성된 이미지 출력
}
