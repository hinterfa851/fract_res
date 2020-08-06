#include </home/dimas/Загрузки/fractol/Minilibx_Installer/fractol.h>

void *render_thread(void *m)
{
	m += 1;
	return(m);
}

int calculate(double i, double j, int mode, t_fractol *fractol)
{
        double counter;
        t_vars *vars;

        vars = malloc(sizeof(t_vars));
//	if (!vars)
//		return NULL;
        if (mode == 0)
                counter = Julia_calculate(i, j, vars, fractol);
        else if (mode == 1)
                counter = Mandelbrot_calculate(i, j, vars, fractol);
        free(vars);
        return (counter);
}

int get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}


int get_color(int counter,int color1,int color2, double num)
{
        int red;
        int green;
        int blue;
        double percentage;
	double test;

	test = counter/(MAXITERATIONS * num * 0.1);
        num = (num) * MAXITERATIONS;

       	percentage = (((int)test)/10.0);
	printf("%f\n", percentage);
        red = get_light((color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF, percentage);
        green = get_light((color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF, percentage);
        blue = get_light(color1 & 0xFF, color2 & 0xFF, percentage);
        return ((red << 16) | (green << 8) | blue);
}

t_fractol alg(t_fractol *fractol)
{
	int color;
	int k;
	int i;
	int j;
	double test;
//	int check;

	i = 0;
	j = 0;
	
	while (i < WIDTH)
        {       while(j < HEIGHT)
                {
  			test = calculate((double)i, (double)j, 0, fractol);
			if (test == MAXITERATIONS)
				color = 0x000000;
			else if (test <= MAXITERATIONS * 1.0/10)
				color = get_color(test, 0x0D1C33, 0x2B6832, 0.1);




				//				color = get_color(test,0xFFFFFF, 0x000000, 0.2);


				//				color = get_color(test, 0xC22121, 0x4F9300, 0.2);
			else
				color = get_color(test, 0x4F9300,0xA1D700,1);




				//color = get_color(test, 0xC22121, 0x4F9300, 0.8);


//				get_color(test, 0xF57336, 0xC22121, 10);
//				color = 0xffffff;
/*	
//			else if (test <MAXITERATIONS/2)
//			{

	//	              color = get_color(test, 0xFFFFFF, 0x000000);
//				printf("%d\t%d\n", color, test);
//				color = get_color(test, 0xC22121, 0x4F9300);
  //               		color = get_color(test, 0x047878, 0x4F9300);
//	         		}

	//		else if (test < MAXITERATIONS*2/3)
          //        	{
	//	  		color = get_color(test,0xFFFFFF, 0x000000);
       //             		color = get_color(test, 0xC22121, 0xFFB733);
	//			printf("%d\n", color);	}
		
			else if (test < MAXITERATIONS/100)
			{
//				test = test * 1.0 /10;
//				color = 0xFFFFFF;
     //                           color = get_color(test, 0xC22121, 0x4F9300);
				color = get_color(test, 0x047878, 0xFFFFFF, 10);
				if (test > 1)
					printf("%d\t%f\n", color, test);
			}
			else if (test < MAXITERATIONS/40)
			       color = get_color(test/2.5, 0xC22121, 0x4F9300, 100);	
//				color = 0xC22121;
		//		color = get_color(test, 0xC22121, 0x000000);
*/
//			else
//				printf("%f\n", test);
				//		color = 0xffffff;
//				get_color(test, 0xF57336, 0xC22121, 10);
		
 		*(int *)(fractol->draw_arr + (i + j*WIDTH)*(fractol->bits_per_pixel/8)) = color;
        //                printf("%d\t%d\n", color, test);
                        j += 1;
                }
                i += 1;
                j = 0;
       }
	return *fractol;
}

int error_handler(char *error)
{
	ft_putendl(error);
	return (1);
}

int main()
{
	t_fractol	*fractol;

	if (!(fractol = malloc(sizeof(t_fractol))))
		return(error_handler("memory error"));
	fractol->X = 0.0;
	fractol->Y = 0.0;
	fractol->Z = 1.0;
	fractol->conn_id = mlx_init();
        fractol->win_id = mlx_new_window(fractol->conn_id, WIDTH, HEIGHT, "fractol");
        fractol->image_id = mlx_new_image(fractol->conn_id, WIDTH, HEIGHT);
        fractol->draw_arr = mlx_get_data_addr(fractol->image_id, &(fractol->bits_per_pixel), &(fractol->size_line), &(fractol->endian));
	alg(fractol);
        mlx_put_image_to_window(fractol->conn_id, fractol->win_id, fractol->image_id, 0, 0);
	mlx_hook(fractol->win_id, 2, 1, key_delay, (void *)fractol);
	mlx_loop(fractol->conn_id);
        return(0);
}  
