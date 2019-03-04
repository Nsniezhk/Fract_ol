/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsniezhk <nsniezhk@student.ua>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 18:51:18 by nsniezhk          #+#    #+#             */
/*   Updated: 2018/10/11 18:51:19 by nsniezhk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "libft.h"
#include "mlx.h"
#include <pthread.h>

void				*fractal(void *fr)
{
	t_fractol	*fract;
	int			x;
	int			y;

	fract = (t_fractol*)fr;
	y = ((WIN_HEIGHT / THREADS) * fract->thread) - 1;
	while (++y < ((WIN_HEIGHT / THREADS) * (fract->thread + 1)))
	{
		x = -1;
		while (++x < WIN_WIDTH)
			*(int*)(fract->mlx->img->ptr + ((x + y * WIN_WIDTH)
				* fract->mlx->img->bpp)) = fract->func(&(*fract), x, y);
	}
	pthread_exit(0);
}

void				redraw(t_fractol *fr)
{
	pthread_t			th[THREADS];
	pthread_attr_t		attr[THREADS];
	t_fractol			fractol_s[THREADS];
	int					i;

	i = -1;
	while (++i < THREADS)
	{
		fractol_s[i] = *fr;
		fractol_s[i].thread = i;
		pthread_attr_init(&attr[i]);
		pthread_create(&th[i], &attr[i], fractal, &fractol_s[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(th[i], NULL);
	mlx_put_image_to_window(fr->mlx->mlx, fr->mlx->window,
		fr->mlx->img->image, 0, 0);
}
