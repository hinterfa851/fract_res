#include "./fractol.h"

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(int counter,int color1,int color2, double num)
{
	int red;
	int green;
	int blue;
	double percentage;
	double test;

//	test = counter / (MAXITERATIONS * num * 0.1);
	test = (double) counter;
	num = (num) * MAXITERATIONS;
	if (num != 1)
	{
		percentage = test / 50;
	}
	else
	    percentage = ((test) / 500.0 );
//	printf("%f\t%f\n", percentage, test);
    red = get_light((color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF, percentage);
    green = get_light((color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF, percentage);
    blue = get_light(color1 & 0xFF, color2 & 0xFF, percentage);
    return ((red << 16) | (green << 8) | blue);
}
