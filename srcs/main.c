#include "../includes/fractol.h"

//main에서 받아온 인자로 프렉탈 구조체를 초기화하는 함수
void	init_fractal(t_fractol *f, int argc, char **argv)
{
	if (*argv[1] == 'j')
		f->blueprint = julia; //첫 인자가 j면 줄리아로 설계예정
	else if (*argv[1] == 'm')
		f->blueprint = mandelbrot; //첫인자가 m이면 망델브로로 설계예정
	else
		f->blueprint = bonus; //첫인자가 b면 추가한 프렉탈로 설계예정
	f->xr = -2.0; //
	f->yi = -2.0;
	f->iter_max = 500; //등비급수의 최대 n을 기본 500으로 설정 
	if (argv[2])
		f->iter_max = ft_atoi(argv[2]); //만약 등비급수의 횟수가 인자로 들어오면 그 횟수만큼 지정
	f->cr = 0.0; //복소수 실수부분 초기화
	f->ci = 0.0; //복소수 허수부분 초기화
	if (argv[3] && argc > 3)
		f->cr = a2f(argv[3]); //3번째 인자가 있다면 복소수의 실수값에 대입
	if (argv[4] && argc > 3)
		f->ci = a2f(argv[4]); //4번째 인자가 있다면 복소수의 허수값에 대입
	f->scale = RESOULTION / 4;
	f->r_rgb = 0x00; /*rgb값 모두 0으로 초기화 */
	f->g_rgb = 0x00;
	f->b_rgb = 0x00;
}

//mlx를 초기화하고 구조체에 담긴 정보로 프렉탈을 그리는 함수
void	set_screen(t_fractol *f)
{
	f->mlx.mlx = mlx_init();//mlx와 연결한다.
	if (f->mlx.mlx == NULL)
		exit(0);
	f->mlx.win = mlx_new_window(f->mlx.mlx, RESOULTION, RESOULTION, "fractol"); //해상도와 창 상단 문자를 지정한다.
	if (f->mlx.win == NULL)
		exit(0);
	f->mlx.img = mlx_new_image(f->mlx.mlx, RESOULTION, RESOULTION); //지정한 해상도만큼 이미지를 생성.
	if (f->mlx.img == NULL)
		exit(0);
	f->mlx.addr = mlx_get_data_addr(f->mlx.img, &f->mlx.bpp, //생성한이미지로 색상을 넣을 전체픽셀의[0,0]주소를 얻는다.(한 픽셀당 4바이트씩 사용예정).
			&f->mlx.size_line, &f->mlx.endian);
	if (f->mlx.addr == NULL)
		exit(0);
	mlx_mouse_hook(f->mlx.win, wheel, f); //마우스의 동작을 설정.
	mlx_key_hook(f->mlx.win, press, f); //키보드의 동작을 설정.
	draw_fractal(f); //프렉탈 그리기.
	mlx_loop(f->mlx.mlx); //창을 계속 띄운다.
}

//안내창을 띄우는 함수
void	man(void)
{
	printf("usage: fractol [fractal type] [iteration] [2 EXTRA OPTION]\n");
	printf("OPTION - fractal type: j(Julia), m(Mandelbrot), b(bonus)\n");
	printf("OPTION - iteration: set interation of fractal\n");
	printf("EXTRA OPTION(Julia Only):\n>>> ");
	printf("fractol ... [real complex number] [imaginary complex number]");
	printf("(ex 0.1 : use only a float)\n");
	exit(0);
}

//인자를 검사하는 함수
int	check_argv(char **argv)
{
	if (ft_strlen(argv[1]) > 1) //첫번째 인자가 1글자 초과면 에러
		return (1);
	if (*argv[1] != 'j' && *argv[1] != 'm' && *argv[1] != 'b') //j,m,b 중에 없으면 에러
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractol	f;

	if (argc == 1 || argc > 5) //인자가 1 ~ 4개가 아니면 안내창 출력
		man();
	else if (check_argv(argv)) //인자의 형식이 안내사항과 다르면  안내창 출력
		man();
	else if (argc > 3 && *argv[1] != 'j') //인자가 2개를 초과하는데 줄리아가 아니면 안내창 출력
		man();
	init_fractal(&f, argc, argv); //프렉탈 구조체 초기화
	set_screen(&f); //mlx로 프렉탈 띄우기
	return (0);
}
