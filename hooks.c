/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:54:22 by achepurn          #+#    #+#             */
/*   Updated: 2018/09/01 13:54:24 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_hook(int button, int x, int y, void *param)
{
	t_mlx	*mlx;
	int		i;

	mlx = (t_mlx *)param;
	if (button == 4 || button == 5 || button == 1)
	{
		i = -1;
		while (++i < TNUM)
		{
			if (button == 4)
			{
				mlx->imgs[i].zoom /= 1.1;
				if (mlx->imgs[i].zoom == 0.0)
					mlx->imgs[i].zoom = 0.1;
			}
			else if (button == 5)
			{
				mlx->imgs[i].zoom *= 1.1;
			}
			else if (button == 1)
				mlx->imgs[i].color = !mlx->imgs[i].color;
		}
	}
	create_fractol(mlx);
	return (1);
}

int		key_hook(int keycode, void *param)
{
	t_mlx	*mlx;
	int		i;

	mlx = (t_mlx *)param;
	if (keycode == 53)
	{
		exit(0);
		free(mlx->imgs);
	}
	i = -1;
	while (++i < TNUM)
	{
		if (keycode == 124)
			mlx->imgs[i].shift.re -= 10 / mlx->imgs[i].zoom;
		else if (keycode == 123)
			mlx->imgs[i].shift.re += 10 / mlx->imgs[i].zoom;
		else if (keycode == 125)
			mlx->imgs[i].shift.im -= 10 / mlx->imgs[i].zoom;
		else if (keycode == 126)
			mlx->imgs[i].shift.im += 10 / mlx->imgs[i].zoom;
	}
	create_fractol(mlx);
	return (1);
}

int		mouse_coords_hook(int x, int y, void *param)
{
	t_mlx	*mlx;
	int		i;

	mlx = (t_mlx *)param;
	i = -1;
	while (++i < TNUM)
	{
		if (x >= 0 && y >= 0 && x < WIN_X && y < WIN_Y)
		{
			mlx->imgs[i].coords.re = (double)x / WIN_X;
			mlx->imgs[i].coords.im = (double)y / WIN_Y;
		}
	}
	create_fractol(mlx);
	return (1);
}
