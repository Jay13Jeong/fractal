#include "../includes/fractol.h"

//화면 스케일을 확대처리하는 함수
int	zoom_in(int x, int y, t_fractol *f)
{
	double	scale_multi; //새로 지정할 구역의 틀

	if (f->scale >= SCALE_MAX) //현재스케일이 최대 스케일을 넘으려면 아무동작 안함
		return (0);
	scale_multi = f->scale * IRIS; //상수로 설정한 배율만큼의 스케일 틀 만들기.
	//x좌표를 마우스로 지정한 위치를 기준으로 스케일하고, 스케일된 화면기준으로 가장 왼쪽x좌표를 가리키게 한다.
	f->xr = ((double)x / f->scale + f->xr) - ((double)x / scale_multi);
	//y좌표를 마우스로 지정한 위치를 기준으로 스케일하고, 스케일된 화면기준으로 가장 상단y좌표를 가리키게 한다.
	f->yi = ((double)y / f->scale + f->yi) - ((double)y / scale_multi);  
	f->scale *= IRIS; //보여줄 범위(스케일)을 배율만큼 재설정한다.
	return (1);
}

//화면 스케일을 축소처리하는 함수
int	zoom_out(int x, int y, t_fractol *f)
{
	double	scale_multi;

	if (f->scale <= RESOULTION / 6) //현재스케일이 기본 해상도 스케일보다 두배이상 축소하려고하면 아무동작 안함
		return (0);
	scale_multi = f->scale / IRIS; //상수로 설정한 배율만큼의 스케일 틀 만들기.
	//x좌표를 마우스로 지정한 위치를 기준으로 스케일하고, 스케일된 화면기준으로 가장 왼쪽x좌표를 가리키게 한다.
	f->xr = ((double)x / f->scale + f->xr) - ((double)x / scale_multi);
	//y좌표를 마우스로 지정한 위치를 기준으로 스케일하고, 스케일된 화면기준으로 가장 상단y좌표를 가리키게 한다.
	f->yi = ((double)y / f->scale + f->yi) - ((double)y / scale_multi);
	f->scale /= IRIS; //보여줄 범위(스케일)을 배율만큼 재설정한다.
	return (1);
}

//마우스의 이벤트를 처리하는 함수
int	wheel(int input, int x, int y, t_fractol *f)
{
	if (input == WHEEL_UP)
	{
		if (!zoom_out(x, y, f)) //마우스 휠을 올리면 축소
			return (0);
	}
	else if (input == WHEEL_DOWN)
	{
		if (!zoom_in(x, y, f)) //마우스 휠을 내리면 확대
			return (0);
	}
	else
		return (0);
	draw_fractal(f); //새로바뀐 장면 적용
	return (0);
}

//키보드 입력을 처리하는 함수
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
