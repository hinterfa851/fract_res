#include "./fractol.h"

int	color_helper(int i, int j, t_helper *helper)
{
	int test;
	int color;

	test = calculate((double)i, (double)j,
			helper->fractol->fract_n, helper->fractol);
	if (test == MAXITERATIONS)
		color = 0x000000;
	else if (test <= MAXITERATIONS * 1.0 / 10)
		color = get_color(test, 0x0D1C33, 0x2B6832, 0.1);
	else
		color = get_color(test, 0x4F9300, 0xA1D700, 1);
	return (color);
}

void	*render_thread(t_helper *helper)
{
	int	i;
	int	j;
	int	color;
	int	num2;

	j = 0;
	i = (helper->n) * HEIGHT / THREADS;
	num2 = (helper->n + 1) * HEIGHT / THREADS;
	while (i < num2)
	{
		while (j < WIDTH)
		{
			color = color_helper(i, j, helper);
			*(int *)(helper->fractol->draw_arr +
					(i + j * WIDTH) * (helper->fractol->bpp / 8)) = color;
			j += 1;
		}
		j = 0;
		i += 1;
	}
	return (void *)"test";
}

int	calculate(double i, double j, int mode, t_fractol *fractol)
{
	double counter;
	t_vars *vars;

	counter = 0.0;
	if (!(vars = malloc(sizeof(t_vars))))
		error_handler("memory error");
	if (mode == 0)
		counter = julia_calculate(i, j, vars, fractol);
	else if (mode == 1)
		counter = mandelbrot_calculate(i, j, vars, fractol);
	else if (mode == 2)
		counter = burning_ship_calculate(i, j, vars, fractol);
	free(vars);
	return (counter);
}

t_fractol		alg(t_fractol *fractol)
{
	int			k;
	int			res;
	pthread_t	*thread;
	t_sender	*sender;

	k = 0;
	if (!(thread = malloc(sizeof(pthread_t) * THREADS)))
		error_handler("memory error");
	if (!(sender = malloc(sizeof(t_sender))))
		error_handler("memory error");
	while (k < THREADS)
	{
		sender->send[k].n = k;
		sender->send[k].fractol = fractol;
		res = pthread_create(thread + k, NULL,
				(void *)render_thread, &(sender->send[k]));
		k++;
	}
	k = 0;
	while (k < THREADS)
		pthread_join(thread[k++], NULL);
	free(thread);
	free(sender);
	return (*fractol);
}

int	main(int argc, char **argv)
{
	t_fractol	*fractol;

	if (!(fractol = malloc(sizeof(t_fractol))))
		return (error_handler("memory error"));
	if (argc != 2)
		error_handler(ERROR);
	fractol->X = 0.0;
	fractol->Y = 0.0;
	fractol->Z = 1.0;
	fractol->d_Re = 0.77015;
	fractol->fract_n = match_fractal(argv[1]);
	fractol->conn_id = mlx_init();
	fractol->win_id = mlx_new_window(
			fractol->conn_id, WIDTH, HEIGHT, "fractol");
	fractol->image_id = mlx_new_image(fractol->conn_id, WIDTH, HEIGHT);
	fractol->draw_arr = mlx_get_data_addr(fractol->image_id,
			&(fractol->bpp), &(fractol->size_line), &(fractol->endian));
	alg(fractol);
	mlx_put_image_to_window(fractol->conn_id,
			fractol->win_id, fractol->image_id, 0, 0);
	mlx_hook(fractol->win_id, 6, 1, mouse_move, (void *)fractol);
	mlx_hook(fractol->win_id, 4, 1, mouse_press, (void *)fractol);
	mlx_hook(fractol->win_id, 2, 1, key_delay, (void *)fractol);
	mlx_loop(fractol->conn_id);
	return (0);
}
