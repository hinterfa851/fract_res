#include "./fractol.h"

void	work(t_fractol *fractol)
{
	fractol->image_id = mlx_new_image(fractol->conn_id, WIDTH, HEIGHT);
	fractol->draw_arr = mlx_get_data_addr(fractol->image_id, &(fractol->bpp),
			&(fractol->size_line), &(fractol->endian));
	alg(fractol);
	mlx_clear_window(fractol->conn_id, fractol->win_id);
	mlx_put_image_to_window(fractol->conn_id,
			fractol->win_id, fractol->image_id, 0, 0);
}

int		key_delay(int key, t_fractol *fractol)
{
	if (key == 0)
	{
		fractol->X += -80.0 / fractol->Z;
		work(fractol);
	}
	else if (key == 2)
	{
		fractol->X += 80.0 / fractol->Z;
		work(fractol);
	}
	else if (key == 1)
	{
		fractol->Y -= 80.0 / fractol->Z;
		work(fractol);
	}
	else if (key == 53)
		exit(21);
	else if ((key == 24) || (key == 27) || (key == 13))
		key_delay2(key, fractol);
	return (0);
}

int		key_delay2(int key, t_fractol *fractol)
{
	if (key == 24)
	{
		fractol->Z *= 2;
		work(fractol);
	}
	else if (key == 27)
	{
		fractol->Z /= 2;
		work(fractol);
	}
	else if (key == 13)
	{
		fractol->Y += 80.0 / fractol->Z;
		work(fractol);
	}
	return (0);
}

int		mouse_move(int x, int y, t_fractol *fractol)
{
	if ((fractol->fract_n == 0) && (x <= WIDTH && x >= 0)
			&& (y <= HEIGHT && y >= 0))
	{
		fractol->d_Re = 0.5 * (x * 1.0) / WIDTH + 0.29015;
		work(fractol);
	}
	return (0);
}

int		mouse_press(int button, int x, int y, t_fractol *fractol)
{
	x = y + 1;
	if (button == 4)
	{
		fractol->Z *= 2;
		work(fractol);
	}
	else if (button == 5)
	{
		fractol->Z /= 2;
		work(fractol);
	}
	return (0);
}
