#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>

#define WIN_X 1000
#define WIN_Y 600
#define FNUM 2
#define TNUM 10

typedef struct		s_complex
{
	double			re;
	double			im;
}					t_complex;

typedef struct 		s_vector2
{
	double			x;
	double			y;
}					t_vector2;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
}					t_mlx;

void			julia(double x, double y, t_mlx *mlx);
void			mandelbrot(double x, double y, t_mlx *mlx);

#endif