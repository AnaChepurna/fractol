#include "fractol.h"

static void init(t_mlx *mlx, char *name, int (*fractol)(t_vector2, t_img *)) {
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
			mlx->imgs[i].shift.re = 0;
			mlx->imgs[i].shift.im = 0;
			mlx->imgs[i].zoom = 1;
			mlx->imgs[i].coords.re = 0.3;
			mlx->imgs[i].coords.im = 0.6;
			mlx->imgs[i].color = 0;
		}
	}
}

static void *draw_fractol(void *img_void) {
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

void create_fractol(t_mlx *mlx) {
	pthread_t tids[TNUM];
	int i;

	i = -1;
	while (++i < TNUM)
		pthread_create(&tids[i], NULL, draw_fractol, &(mlx->imgs[i]));
	while (i--)
		pthread_join(tids[i], NULL);
	while (++i < TNUM)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->imgs[i].img, 0, mlx->imgs[i].y);
}

static void run_fractol(char *fractol_name) {
	static char *fractols[FNUM] = {"Mandelbrot", "Julia", "sin"};
	static int (*f[FNUM])(t_vector2, t_img *) = {mandelbrot, julia, sinus};
	t_mlx mlx;
	int i;

	i = -1;
	while (++i < FNUM)
	{
		if (ft_strequ(fractols[i], fractol_name))
		{
			init(&mlx, fractol_name, f[i]);
			mlx_hook(mlx.win, 2, 1L << 0, key_hook, &mlx);
			mlx_hook(mlx.win, 6, 1L << 6, mouse_coords_hook, &mlx);
			mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
			create_fractol(&mlx);
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