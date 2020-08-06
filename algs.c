#include "./fractol.h"

int	julia_calculate(double i, double j, t_vars *vars, t_fractol *fractol)
{
	int counter;

	vars->cRe = -0.7;
	vars->cIm = fractol->d_Re;
	counter = 0;
	vars->newRe = (i - WIDTH / 2 + fractol->Y) / (0.25 * WIDTH * fractol->Z);
	vars->newIm = (j - HEIGHT / 2 + fractol->X) / (0.25 * HEIGHT * fractol->Z);
	while (counter < MAXITERATIONS)
	{
		vars->oldRe = vars->newRe;
		vars->oldIm = vars->newIm;
		vars->newRe = vars->oldRe * vars->oldRe
			- vars->oldIm * vars->oldIm + vars->cRe;
		vars->newIm = 2 * vars->oldRe * vars->oldIm + vars->cIm;
		if ((vars->newRe * vars->newRe + vars->newIm * vars->newIm) > 4)
			return (counter);
		counter += 1;
	}
	return (counter);
}

int	mandelbrot_calculate(double i, double j, t_vars *vars, t_fractol *fractol)
{
	double counter;

	vars->cRe = 0;
	vars->cIm = 0;
	counter = 0;
	vars->newRe = 0;
	vars->newIm = 0;
	vars->pr = ((i - WIDTH / 2)) / (0.25 * WIDTH * fractol->Z)
		+ fractol->X / (WIDTH);
	vars->pi = ((j - HEIGHT / 2)) / (0.25 * HEIGHT * fractol->Z)
		+ fractol->Y / (HEIGHT);
	while (counter < MAXITERATIONS)
	{
		vars->oldRe = vars->newRe;
		vars->oldIm = vars->newIm;
		vars->newRe = vars->oldRe * vars->oldRe
			- vars->oldIm * vars->oldIm + vars->cRe + vars->pr;
		vars->newIm = 2 * vars->oldRe * vars->oldIm + vars->cIm + vars->pi;
		if ((vars->newRe * vars->newRe + vars->newIm * vars->newIm) > 4)
			return (counter);
		counter += 1;
	}
	return (counter);
}

/*
int Newton_calculate(double i, double j, t_vars *vars, t_fractol *fractol)
{
	double counter;
	double deltha;
	double zx;
	double zy;
	double del;

	deltha = 0.000001;
	vars->cRe = 0;
        vars->cIm = 0;
        counter = 0;

        vars->newRe = vars->newIm = 0;
        vars->pr = ((i - WIDTH/2 ))/( 0.25 * WIDTH * fractol->Z) + fractol->X/(WIDTH);
        vars->pi = ((j - HEIGHT/2 ))/( 0.25 * HEIGHT * fractol->Z) + fractol->Y/(HEIGHT);
 //       printf("%f\t%f\n", newRe, newIm);
        while (counter < MAXITERATIONS)
        {
		del = pow(vars->pr, 4) + pow(vars->pi, 4) + 2 * pow(vars->pr, 2) * pow(vars->pi, 2);
		zx = ((1.0/3) * (pow(vars->pr, 5) + 2 * pow(vars->pr, 3) * pow(vars->pi, 2) + vars->pr * pow(vars->pi, 4)))/del;
		zy = ((1.0/3) * (pow(vars->pr, 4) * vars->pi + 2 * pow(vars->pr, 2) * pow(vars->pi, 3) + pow(vars->pi, 5)))/del;
		vars->pr -= zx;
		vars->pi -= zy;
		printf("%f\t%f\n", vars->pr, vars->pi);

                if ((fabs(zx - 1) < deltha && fabs(zy - 0) < deltha) || (fabs(zx + 0.5) < deltha && fabs(zy - sqrt(3)/2) < deltha) ||(fabs(zx + 0.5) < deltha && fabs(zy + sqrt(3)/2) < deltha))
                        return (counter);
                counter += 1;
        }
        return (counter);
}
*/

int	burning_ship_calculate(double i, double j, t_vars *vars, t_fractol *fractol)
{
	double counter;

	vars->cRe = 0;
	vars->cIm = 0;
	counter = 0;
	vars->newRe = 0;
	vars->newIm = 0;
	vars->pr = ((i - WIDTH / 2)) / (0.25 * WIDTH * fractol->Z)
		+ fractol->X / (WIDTH);
	vars->pi = ((j - HEIGHT / 2)) / (0.25 * HEIGHT * fractol->Z)
		+ fractol->Y / (HEIGHT);
	while (counter < MAXITERATIONS)
	{
		vars->oldRe = fabs(vars->newRe);
		vars->oldIm = fabs(vars->newIm);
		vars->newRe = vars->oldRe * vars->oldRe - vars->oldIm * vars->oldIm
			+ vars->cRe + vars->pr;
		vars->newIm = 2 * vars->oldRe * vars->oldIm + vars->cIm + vars->pi;
		if ((vars->newRe * vars->newRe + vars->newIm * vars->newIm) > 4)
			return (counter);
		counter += 1;
	}
	return (counter);
}
