#include "fractol.h"

int mouse_hook(int button, int x, int y, void *param) {
	t_mlx *mlx;
	int i;

	mlx = (t_mlx *)param;
	if (button == 4 || button == 5) {
		i = -1;
		while (++i < TNUM) {
			if (button == 4 && mlx->imgs[i].zoom > 0)
				mlx->imgs[i].zoom /= 1.1;
			else if (button == 5) {
				mlx->imgs[i].zoom *= 1.1;
				mlx->imgs[i].shift.x += (WIN_X / 2 - x) / 10 * atan(mlx->imgs[i].zoom);
				mlx->imgs[i].shift.y += (WIN_Y / 2 - y) / 10 * atan(mlx->imgs[i].zoom);
			}
		}
	}
	create_fractol(mlx);
	return (1);
}

int key_hook(int keycode, void *param) {
	t_mlx *mlx;
	int i;

	mlx = (t_mlx *)param;
	i = -1;
	while (++i < TNUM) {
		if (keycode == 124)
			mlx->imgs[i].shift.x -= 10 * atan(mlx->imgs[i].zoom);
		else if (keycode == 123)
			mlx->imgs[i].shift.x += 10 * atan(mlx->imgs[i].zoom);
		else if (keycode == 125)
			mlx->imgs[i].shift.y -= 10 * atan(mlx->imgs[i].zoom);
		else if (keycode == 126)
			mlx->imgs[i].shift.y += 10 * atan(mlx->imgs[i].zoom);
	}
	create_fractol(mlx);
	return 0;
}