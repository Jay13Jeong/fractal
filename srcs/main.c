#include "../includes/fractol.h"

void	init_fractal(t_fractol *f, int argc, char **argv)
{
	if (*argv[1] == 'j')
		f->blueprint = julia;
	else if (*argv[1] == 'm')
		f->blueprint = mandelbrot;
	else
		f->blueprint = bonus;
	f->xr = -2.0;
	f->yi = -2.0;
	f->iter_max = 500;
	if (argv[2])
		f->iter_max = ft_atoi(argv[2]);
	f->cr = 0.0;
	f->ci = 0.0;
	if (argv[3] && argc > 3)
		f->cr = a2f(argv[3]);
	if (argv[4] && argc > 3)
		f->ci = a2f(argv[4]);
	f->scale = RESOULTION / 4;
	f->r_rgb = 0x00;
	f->g_rgb = 0x00;
	f->b_rgb = 0x00;
}

void	set_screen(t_fractol *f)
{
	f->mlx.mlx = mlx_init();
	if (f->mlx.mlx == NULL)
		exit(0);
	f->mlx.win = mlx_new_window(f->mlx.mlx, RESOULTION, RESOULTION, "fractol");
	if (f->mlx.win == NULL)
		exit(0);
	f->mlx.img = mlx_new_image(f->mlx.mlx, RESOULTION, RESOULTION);
	if (f->mlx.img == NULL)
		exit(0);
	f->mlx.addr = mlx_get_data_addr(f->mlx.img, &f->mlx.bpp,
			&f->mlx.size_line, &f->mlx.endian);
	if (f->mlx.addr == NULL)
		exit(0);
	mlx_mouse_hook(f->mlx.win, wheel, f);
	mlx_key_hook(f->mlx.win, press, f);
	draw_fractal(f);
	mlx_loop(f->mlx.mlx);
}

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

int	check_argv(char **argv)
{
	int		i;
	int		compare;
	char	*temp;

	if (ft_strlen(argv[1]) > 1)
		return (1);
	if (*argv[1] != 'j' && *argv[1] != 'm' && *argv[1] != 'b')
		return (1);
	i = 1;
	while (argv[++i])
	{
		if (i == 2)
			temp = ft_itoa(ft_atoi(argv[i]));
		else
			temp = f2a(a2f(argv[i]));
		if (temp == NULL)
			return (1);
		compare = ft_strncmp(argv[i], temp, -1);
		free (temp);
		if (compare)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractol	f;

	if (argc == 1 || argc > 5)
		man();
	else if (check_argv(argv))
		man();
	else if (argc > 3 && *argv[1] != 'j')
		man();
	init_fractal(&f, argc, argv);
	set_screen(&f);
	return (0);
}
