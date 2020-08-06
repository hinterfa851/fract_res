#include "./fractol.h"

int	error_handler(char *error)
{
	ft_putendl(error);
	exit(42);
	return (1);
}

int	match_fractal(char *ffff)
{
	if (ft_strcmp(ffff, "mandelbrot") == 0)
		return (1);
	else if (ft_strcmp(ffff, "julia") == 0)
		return (0);
	else if (ft_strcmp(ffff, "burn") == 0)
		return (2);
	return (42);
}
