#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <sys/mman.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <pthread.h>

#define WIN_X 800
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
	int				x;
	int				y;
}					t_vector2;

typedef struct		s_img
{
	void			*img;
	int				*map;
	int 			(*fractol)(t_vector2, struct s_img *);
	int				y;
	t_complex		shift;
	double			zoom;
}					t_img;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	t_img			*imgs;
}					t_mlx;

void 		create_fractol(t_mlx *mlx);
int			julia(t_vector2 vec, t_img *img);
int			mandelbrot(t_vector2 vec, t_img *img);
int 		mouse_hook(int button, int x, int y, void *param);
int 		key_hook(int keycode, void *param);

#endif