#include "fractol.h"

int			mandelbrot(t_vector2 vec, t_img *img) {
	int res;
	t_complex z;
	t_complex c;
	double tmp;

	res = 0;
	z.re = ((double)vec.x - img->shift.x) / (img->zoom * 200);
	z.im = ((double)vec.y - img->shift.y) / (img->zoom * 200);
	c.re = z.re;
	c.im = z.im;
	//printf("%f, %f\n", z.re, z.im);
	while (res < 256 && fabs(z.re * z.re + z.im * z.im) < 4)
	{
		tmp = z.re;
		z.re = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * tmp * z.im + c.im;
		res++;
	}
	return (res << 2);
}

int			julia(t_vector2 vec, t_img *img) {
	int res;
	t_complex z;
	double tmp;

	res = 0;
	z.re = (vec.x + 0 - 400) / 200;
	z.im = (vec.y + 0 - 400) / -200;
	while (res < 256 && z.re * z.re + z.im * z.im < 4)
	{
	 	tmp = z.re;
		z.re = z.re * z.re - z.im * z.im - 0.8 + 0 / 800;
		z.im = 2 * tmp * z.im + 0 / 800;
		res++;
	}
	(void)img;
	return res;
}