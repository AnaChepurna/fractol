#include "fractol.h"

void put_pixel(t_vector2 vec, t_mlx *mlx, int color) {
	int size;
	int bits;
	int endian;

	mlx->map = (int*)mlx_get_data_addr(mlx->img, &bits, &size, &endian);
	// if (vec.x >= 0 && vec.x <= WIN_X && vec.y >= 0 && vec.y <= WIN_Y)
	// 	mlx->map[(int)vec.y * WIN_Y + (int)vec.x] = color;
	mlx->map[10] = 0xffffff;
	mlx->map[100] = 0xffffff;
	mlx->map[1000] = 0xffffff;
	mlx->map[10000] = 0xffffff;
	(void)vec;
	(void)color;
	//mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	ft_putstr("l");
}

void init(t_mlx *mlx, char *name) {
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_X, WIN_Y, name);
	mlx->img = mlx_new_image(mlx->mlx, WIN_X, WIN_Y);
}

void create_fractol(t_mlx *mlx, int (*fractol)(t_vector2, t_mlx *)) {
	pid_t pids[TNUM];
	t_vector2 vec;
	int i;

	i = -1;
	while (++i < TNUM)
	{
		if (!(pids[i] = fork()))
		{
			vec.x = -1;
			while (++(vec.x) < WIN_X)
			{
				vec.y = i * WIN_Y / TNUM - 1;
				while (++(vec.y) < (i + 1) * WIN_Y / TNUM)
				{
					put_pixel(vec, mlx, 10);
					(void)fractol;
				}
			}
			exit(0);
		}
	}
	while (i-- >= 0)
		wait(&pids[i]);
}

void *run_fractol(void *fractol_name) {
	static char *fractols[FNUM] = {"Mandelbrot", "Julia"};
	static int (*f[FNUM])(t_vector2, t_mlx *) = {mandelbrot, julia};
	t_mlx mlx;
	int i;

	i = -1;
	while (++i < FNUM)
	{
		if (ft_strequ(fractols[i], fractol_name))
		{
			init(&mlx, fractol_name);
			create_fractol(&mlx, f[i]);
			mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
			mlx_loop(mlx.mlx);
			return (NULL);
		}
	}
	return (NULL);
}

int main(int c, char **v) {
	int i;
	pid_t *pids;

	i = 0;
	if (c < 2) {
		ft_putstr("usage : ");
		ft_putstr(v[0]);
		ft_putstr(" [fractol name] ...\n");
		exit(0);
	}
	if ((pids = (pid_t *)malloc(sizeof(pid_t) * (c - 1))))
	{
		while (++i < c)
		{
			if (!(pids[i - 1] = fork())) {
				run_fractol(v[i]);
				exit (0);
			}
		}
		while (i-- > 0)
			wait(&pids[i]);
	}
	free(pids);
}