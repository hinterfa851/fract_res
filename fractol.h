#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 700
# define HEIGHT 700
# define MAXITERATIONS 200
# define GRAD 10
# define THREADS 10

# define ERROR "Add fractal name!\nList of avalble names - mandelbrot, julia, burn."
# define START_COLOR 0x000000
# define END_COLOR 0x05fc1e
# define BLACK 0x000000
# define BLUE 0x052efc
# define YELLOW 0xfcae05
# define WHITE 0xffffff

# include "stdio.h"
# include "stdlib.h"
# include <pthread.h>
# include <math.h>
# include "./minilibx/mlx.h"
# include "./libft/libft.h"


typedef struct		s_fractol
{
	void		*conn_id;
	void		*win_id;
	char		*draw_arr;
	void		*image_id;
	int		endian;
	int		size_line;
	int		bpp;
	double 		X;
	double 		Y;
	double	        Z;
	int		nthread;
	int		fract_n;
	double	d_Re;

}			t_fractol;

typedef struct		s_variables
{
	double		cRe;
	double		cIm;
	double		oldRe;
	double		oldIm;
	double		newRe;
	double		newIm;
	double		pr;
	double		pi;
	double		X;
	double		Y;
	double		Z;
}			t_vars;	

typedef struct          s_help
{
        t_fractol       *fractol;
        int             n;
}                       t_helper;


typedef struct          s_send
{
		t_helper		send[THREADS];
}                       t_sender;

int key_delay2(int key, t_fractol *fractol);

int burning_ship_calculate(double i, double j, t_vars *vars, t_fractol *fractol);

void work(t_fractol *fractol);

int mouse_press(int button, int x, int y, t_fractol *fractol);

int mouse_move(int x, int y, t_fractol *fractol);

int match_fractal(char *ffff);

void *render_thread(t_helper *helper);

int error_handler(char *error);

int key_delay(int key, t_fractol *fractol);

t_fractol alg(t_fractol *fractol);

int get_color(int counter,int color1,int color2, double num);

int get_light(int start, int end, double percentage);

int calculate(double i, double j, int mode, t_fractol *fractol);

int mandelbrot_calculate(double i, double j, t_vars *vars, t_fractol *fractol);

int julia_calculate(double i, double j, t_vars *vars, t_fractol *fractol);

#endif
