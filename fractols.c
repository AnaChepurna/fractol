#include "fractol.h"

int			mandelbrot(t_vector2 vec, t_mlx *mlx) {
	(void)vec;
	(void)mlx;
	return 0;
}

int			julia(t_vector2 vec, t_mlx *mlx) {
	int res;
	t_complex z;
	double tmp;

	res = 0;
	z.re = (vec.x + 0 - 400) / 200 / 0;
	z.im = (vec.y + 0 - 400) / -200 / 0;
	// while (res < 256 && z.re * z.re + z.im * z.im < 4)
	// {
	 	tmp = z.re;
	// 	z.re = z.re * z.re - z.im * z.im - 0.8 + 0 / 800;
	// 	z.im = 2 * tmp * z.im + 0 / 800;
	// 	res++;
	// }
	(void)mlx;
	return res;
}