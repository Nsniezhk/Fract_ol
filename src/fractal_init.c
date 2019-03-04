/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsniezhk <nsniezhk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 02:15:25 by nsniezhk          #+#    #+#             */
/*   Updated: 2018/10/17 02:15:27 by nsniezhk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void			mandelbrot_init(t_fractol *fr)
{
	fr->min->real = -3.0f;
	fr->max->real = 2.0f;
	fr->min->imagine = -1.5f;
	fr->max->imagine = fr->min->imagine +
	(fr->max->real - fr->min->real) * WIN_HEIGHT / WIN_WIDTH;
	fr->depth = 20;
	fr->func = &calculate_mandelbrot;
}

void			julia_init(t_fractol *fr)
{
	fr->min->real = -2.0f;
	fr->max->real = 2.0f;
	fr->min->imagine = -1.2f;
	fr->max->imagine = 1.2f;
	fr->inp->jx = -0.7;
	fr->inp->jy = -0.27015;
	fr->depth = 60;
	fr->func = &calculate_julia;
}

void			burning_ship_init(t_fractol *fr)
{
	fr->min->real = -3.0f;
	fr->max->real = 2.0f;
	fr->min->imagine = -2.0f;
	fr->max->imagine = fr->min->imagine +
	(fr->max->real - fr->min->real) * WIN_HEIGHT / WIN_WIDTH;
	fr->depth = 60;
	fr->func = &burning_ship;
}
