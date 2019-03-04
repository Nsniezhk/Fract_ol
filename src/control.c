/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsniezhk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 18:50:56 by nsniezhk          #+#    #+#             */
/*   Updated: 2018/10/11 18:50:58 by nsniezhk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

static	void		zoom(t_fractol *fr, double step)
{
	double	zoom_step;

	zoom_step = 1.0 / step;
	fr->min->real = (fr->inp->x + (fr->min->real - fr->inp->x) * zoom_step);
	fr->min->imagine = (fr->inp->y +
		(fr->min->imagine - fr->inp->y) * zoom_step);
	fr->max->real = (fr->inp->x + (fr->max->real - fr->inp->x) * zoom_step);
	fr->max->imagine = (fr->inp->y +
		(fr->max->imagine - fr->inp->y) * zoom_step);
}

int					key_down(int key, t_fractol *fr)
{
	if (key == 53)
		exit(EXIT_SUCCESS);
	else if (key == 256)
		fr->inp->mouse_lock = 1;
	else if (key == 257)
		fr->inp->mouse_lock = 0;
	else if (key == 126)
		fr->depth += 1;
	else if (key == 125)
		fr->depth -= 1;
	redraw(&(*fr));
	return (1);
}

int					key_up(int key, t_fractol *fr)
{
	key = 0;
	fr->inp->key = 0;
	return (1);
}

int					mouse_wheel(int button, int x, int y, t_fractol *fr)
{
	x = 0;
	y = 0;
	if (button == 5)
		zoom(&(*fr), 1.1f);
	else if (button == 4)
		zoom(&(*fr), (1.0f / 1.1f));
	redraw(&(*fr));
	return (1);
}

int					mouse_move(int x, int y, t_fractol *fr)
{
	if (fr->inp->mouse_lock == 0)
	{
		fr->inp->jx = (double)x / (WIN_WIDTH /
			(fr->max->real - fr->min->real)) + fr->min->real;
		fr->inp->jy = (double)y / (WIN_HEIGHT /
			(fr->max->imagine - fr->min->imagine)) + fr->min->imagine;
	}
	fr->inp->x = (double)x / (WIN_WIDTH /
		(fr->max->real - fr->min->real)) + fr->min->real;
	fr->inp->y = (double)y / (WIN_HEIGHT /
		(fr->max->imagine - fr->min->imagine)) + fr->min->imagine;
	redraw(&(*fr));
	return (1);
}
