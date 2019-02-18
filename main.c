#include "fractol.h"

void usage(char *program_name) {
	ft_putstr("usage : ");
	ft_putstr(program_name);
	ft_putstr(" [fractol name] ...\n");
	exit(0);
}

void init(t_mlx *mlx, char *name) {
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_X, WIN_Y, name);
	mlx->img = mlx_new_image(mlx->mlx, WIN_X, WIN_Y);
}

void create_fractol(int index, t_mlx *mlx) {
	static void (*fractols[FNUM])(double, double, t_mlx *) = {mandelbrot, julia};
	pid_t pids[TNUM];
	double x;
	double y;
	int i;

	i = -1;
	while (++i < TNUM)
	{
		if (!(pids[i - 1] = fork()))
		{
			x = -1;
			while (++x < WIN_X)
			{
				y = i * WIN_Y / TNUM - 1;
				while (++y < (i + 1) * WIN_Y / TNUM)
				{
					fractols[index](x, y, mlx);
				}
			}
		}
	}
	while (i-- >= 0)
		wait(&pids[i]);
}

void *run_fractol(void *fractol_name) {
	static char *fractols[FNUM] = {"Mandelbrot", "Julia"};
	t_mlx mlx;
	int i;

	i = -1;
	while (++i < FNUM)
	{
		if (ft_strequ(fractols[i], fractol_name))
		{
			init(&mlx, fractol_name);
			create_fractol(i, &mlx);
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
	if (c < 2)
		usage(v[0]);
	if ((pids = (pid_t *)malloc(sizeof(pid_t) * (c - 1))))
	{
		while (++i < c)
		{
			if (!(pids[i - 1] = fork()))
				run_fractol(v[i]);
		}
		while (i-- > 0)
			wait(&pids[i]);
	}
	free(pids);
}