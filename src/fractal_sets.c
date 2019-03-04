/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_sets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsniezhk <nsniezhk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:57:40 by nsniezhk          #+#    #+#             */
/*   Updated: 2018/10/11 15:57:42 by nsniezhk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include <math.h>
#include "colors.h"

int				calculate_mandelbrot(t_fractol *fr, int x, int y)
{
	t_complex	z;
	t_complex	z2;
	double		real;
	double		imagine;

	real = ((double)x / WIN_WIDTH) *
	(fr->max->real - fr->min->real) + fr->min->real;
	imagine = ((double)y / WIN_HEIGHT) *
	(fr->max->imagine - fr->min->imagine) + fr->min->imagine;
	z.real = real;
	z.imagine = imagine;
	fr->step = -1;
	while (++fr->step < fr->depth)
	{
		z2.real = z.real * z.real;
		z2.imagine = z.imagine * z.imagine;
		if (z2.real + z2.imagine > 4)
			break ;
		z.imagine = 2 * z.real * z.imagine + imagine;
		z.real = z2.real - z2.imagine + real;
	}
	return ((fr->step == fr->depth) ? 0x000000 : colors[fr->step % 20].color);
}

int				calculate_julia(t_fractol *fr, int x, int y)
{
	t_complex	z;
	t_complex	z2;

	z.real = ((double)x / WIN_WIDTH) *
	(fr->max->real - fr->min->real) + fr->min->real;
	z.imagine = ((double)y / WIN_HEIGHT) *
	(fr->max->imagine - fr->min->imagine) + fr->min->imagine;
	fr->step = -1;
	while (++fr->step < fr->depth)
	{
		z2.real = z.real * z.real;
		z2.imagine = z.imagine * z.imagine;
		if (z2.real + z2.imagine > 4)
			break ;
		z.imagine = 2 * z.real * z.imagine + fr->inp->jy;
		z.real = z2.real - z2.imagine + fr->inp->jx;
	}
	return ((fr->step == fr->depth) ? 0x000000 : colors[fr->step % 20].color);
}

int				burning_ship(t_fractol *fr, int x, int y)
{
	t_complex	z;
	t_complex	z2;
	double		real;
	double		imagine;

	real = ((double)x / WIN_WIDTH) *
	(fr->max->real - fr->min->real) + fr->min->real;
	imagine = ((double)y / WIN_HEIGHT) *
	(fr->max->imagine - fr->min->imagine) + fr->min->imagine;
	z.real = real;
	z.imagine = imagine;
	fr->step = -1;
	while (++fr->step < fr->depth)
	{
		z.real = fabs(z.real);
		z.imagine = fabs(z.imagine);
		z2.real = z.real * z.real - z.imagine * z.imagine + real;
		z2.imagine = z.real * z.imagine * 2 + imagine;
		if (z2.real + z2.imagine > 4)
			break ;
		z.real = z2.real;
		z.imagine = z2.imagine;
	}
	return ((fr->step == fr->depth) ? 0x000000 : colors[fr->step % 20].color);
}
