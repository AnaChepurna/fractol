#include "fractol.h"

void init(t_mlx *mlx, char *name, int (*fractol)(t_vector2, t_img *)) {
	int sbe[3];
	int i;

	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_X, WIN_Y, name);
	if ((mlx->imgs = (t_img *)malloc(sizeof(t_img) * TNUM))) {
		i = -1;
		while (++i < TNUM)
		{
			mlx->imgs[i].img = mlx_new_image(mlx->mlx, WIN_X, WIN_Y / TNUM);
			mlx->imgs[i].map = (int*)mlx_get_data_addr(mlx->imgs[i].img, &sbe[0],
				&sbe[1], &sbe[2]);
			mlx->imgs[i].y = i * WIN_Y / TNUM;
			mlx->imgs[i].fractol = fractol;
		}
	}
}

void *create_fractol(void *img_void) {
	t_vector2 vec;
	t_img *img;

	img = (t_img *)img_void;
	vec.x = -1;
	while (++(vec.x) < WIN_X) {
		vec.y = img->y - 1;
		while (++(vec.y) < img->y + WIN_Y / TNUM)
			img->map[(vec.y - img->y) * WIN_X + vec.x] = img->fractol(vec, img);
	}
	return (NULL);
}

void run_fractol(char *fractol_name) {
	static char *fractols[FNUM] = {"Mandelbrot", "Julia"};
	static int (*f[FNUM])(t_vector2, t_img *) = {mandelbrot, julia};
	pthread_t tids[TNUM];
	t_mlx mlx;
	t_vector2 vec;

	vec.x = -1;
	while (++(vec.x) < FNUM)
	{
		if (ft_strequ(fractols[vec.x], fractol_name))
		{
			init(&mlx, fractol_name, f[vec.x]);
			vec.y = -1;
			while (++(vec.y) < TNUM)
				pthread_create(&tids[vec.y], NULL, create_fractol, &(mlx.imgs[vec.y]));
			while ((vec.y)--)
				pthread_join(tids[vec.y], NULL);
			while (++(vec.y) < TNUM)
				mlx_put_image_to_window(mlx.mlx, mlx.win,
					mlx.imgs[vec.y].img, 0, mlx.imgs[vec.y].y);
			mlx_loop(mlx.mlx);
			break;
		}
	}
}

int main(int c, char **v) {
	int i;
	pid_t *pids;
	t_mlx mlx;

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
				run_fractol(v[1]);
				exit (0);
			}
		}
		while (i-- > 0)
			wait(&pids[i]);
	}
	free(pids);
}