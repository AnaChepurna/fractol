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

int			mandelbrot(t_vector2 vec, t_img *img)
{
	int			res;
	t_complex	z;
	t_complex	c;
	double		tmp;

	res = 0;
	z.re = ((double)vec.x - 500 - img->shift.re * img->zoom) /
	(img->zoom * 200);
	z.im = ((double)vec.y - 300 - img->shift.im * img->zoom) /
	(img->zoom * 200);
	c.re = z.re;
	c.im = z.im;
	while (res < 256 && fabs(z.re * z.re + z.im * z.im) < 4)
	{
		tmp = z.re;
		z.re = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * tmp * z.im + c.im;
		res++;
	}
	if (img->color)
		return (res << 2 | res << 9 | res << 20);
	return (res << 2);
}

int			julia(t_vector2 vec, t_img *img)
{
	int			res;
	t_complex	z;
	double		tmp;

	res = 0;
	z.re = ((double)vec.x - 400 - img->shift.re * img->zoom) /
	(img->zoom * 200);
	z.im = ((double)vec.y - 300 - img->shift.im * img->zoom) /
	(img->zoom * 200);
	while (res < 256 && fabs(z.re * z.re + z.im * z.im) < 4)
	{
		tmp = z.re;
		z.re = z.re * z.re - z.im * z.im - img->coords.re;
		z.im = 2 * tmp * z.im + img->coords.im;
		res++;
	}
	if (img->color)
		return (res << 2 | res << 19);
	return (res << 2);
}

int			sinus(t_vector2 vec, t_img *img)
{
	int			res;
	t_complex	z;
	double		tmp;

	res = 0;
	z.re = ((double)vec.x - 400 - img->shift.re * img->zoom) /
	(img->zoom * 200);
	z.im = ((double)vec.y - 300 - img->shift.im * img->zoom) /
	(img->zoom * 200);
	while (res < 50 && fabs(z.re * z.re + z.im * z.im) < 40)
	{
		tmp = z.re;
		z.re = sin(z.re) * cosh(z.im) * 1.5;
		z.im = cos(tmp) * sinh(z.im) * 1.5;
		res++;
	}
	if (img->color)
		return (res << 6 | res << 11);
	return (res << 4);
}

int			cosinus(t_vector2 vec, t_img *img)
{
	int			res;
	t_complex	z;
	double		tmp;

	res = 0;
	z.re = ((double)vec.x - 400 - img->shift.re * img->zoom) /
	(img->zoom * 200);
	z.im = ((double)vec.y - 300 - img->shift.im * img->zoom) /
	(img->zoom * 200);
	while (res < 50 && fabs(z.re * z.re + z.im * z.im) < 40)
	{
		tmp = z.re;
		z.re = cos(z.re) * cosh(z.im) * 1.5;
		z.im = sin(tmp) * sinh(z.im) * 1.5 * -1;
		res++;
	}
	if (img->color)
		return (res << 8 | res << 16 | res << 21);
	return (res << 4);
}
