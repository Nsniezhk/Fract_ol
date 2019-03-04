/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsniezhk <nsniezhk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:16:12 by nsniezhk          #+#    #+#             */
/*   Updated: 2018/10/08 17:16:14 by nsniezhk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fract_ol.h"
#include "libft.h"
#include "ft_printf.h"
#include <errno.h>

static	void			show_usage(void)
{
	ft_printf("\x1b[32m");
	ft_printf("___________________________________________________\n");
	ft_printf("|||||                 Fract'ol                |||||\n");
	ft_printf("|*************************************************|\n");
	ft_printf("|                                                 |\n");
	ft_printf("| [USAGE]> ./fract'ol [fractal_set]               |\n");
	ft_printf("|                                                 |\n");
	ft_printf("|*************************************************|\n");
	ft_printf("|  AVAILABLE SETS:                                |\n");
	ft_printf("|  ,___________________________________________   |\n");
	ft_printf("|  | [Mandelbrot]                              |  |\n");
	ft_printf("|  | type:'Mandelbrot' 'mandelbrot'     or '1' |  |\n");
	ft_printf("|  | [Julia]                                   |  |\n");
	ft_printf("|  | type:'Julia' 'julia'               or '2' |  |\n");
	ft_printf("|  | [burning_ship]                            |  |\n");
	ft_printf("|  | type:'Burning_ship' 'burning_ship' or '3' |  |\n");
	ft_printf("|  |___________________________________________|  |\n");
	ft_printf("|                                                 |\n");
	ft_printf("|*************************************************|\n");
	ft_printf("|___________________[nsniezhk]____________________|\n");
}

static	int				return_error(int error, int er)
{
	ft_printf("\x1b[31m""[Fract'ol] ERROR: ");
	if (error != 0)
	{
		if (error == EISDIR)
			ft_printf("\x1b[33m""directory as argument!\n");
		if (error == ENOENT)
			ft_printf("\x1b[33m""File is not valid or doesn't exist!\n");
		return (0);
	}
	if (er == 1 || er == 2 || er == 3)
	{
		if (er == 1)
			ft_printf("\x1b[33m""Wrong number of arguments!\n");
		if (er == 2)
			ft_printf("\x1b[33m""Fractol structure initialization failed!");
		if (er == 3)
			ft_printf("\x1b[33m""Fractal set is not supported!\n");
		show_usage();
		return (0);
	}
	return (ft_printf("UNDEFINED ERROR!\n"));
}

static	t_fractol		*structure_malloc(char *title)
{
	t_fractol *fr;

	if ((fr = ft_memalloc(sizeof(t_fractol))) == NULL ||
		(fr->min = ft_memalloc(sizeof(t_complex))) == NULL ||
		(fr->max = ft_memalloc(sizeof(t_complex))) == NULL ||
		(fr->inp = ft_memalloc(sizeof(t_control))) == NULL ||
		(fr->mlx = ft_memalloc(sizeof(t_mlx))) == NULL ||
		(fr->mlx->mlx = mlx_init()) == NULL ||
		(fr->mlx->window = mlx_new_window(fr->mlx->mlx, WIN_WIDTH, WIN_HEIGHT,
			title)) == NULL ||
		(fr->mlx->img = ft_memalloc(sizeof(t_image))) == NULL ||
		(fr->mlx->img->image =
			mlx_new_image(fr->mlx->mlx, WIN_WIDTH, WIN_HEIGHT)) == NULL ||
		(fr->mlx->img->ptr =
			mlx_get_data_addr(fr->mlx->img->image, &fr->mlx->img->bpp,
				&fr->mlx->img->stride, &fr->mlx->img->endian)) == NULL)
		return (NULL);
	fr->mlx->img->bpp /= 8;
	fr->depth = 200;
	fr->inp->mouse_lock = 0;
	ft_strdel(&title);
	return (fr);
}

static	t_fractol		*fractol_init(char *title)
{
	t_fractol	*fr;

	if ((fr = structure_malloc(
		ft_strjoin("Fract'ol [nsniezhk] ", title))) == NULL)
		return (NULL);
	if (!ft_strcmp(title, "Mandelbrot") ||
		!ft_strcmp(title, "mandelbrot") || !ft_strcmp(title, "1"))
		mandelbrot_init(&(*fr));
	else if (!ft_strcmp(title, "Julia") ||
		!ft_strcmp(title, "julia") || !ft_strcmp(title, "2"))
		julia_init(&(*fr));
	else if (!ft_strcmp(title, "Burning_ship") ||
		!ft_strcmp(title, "burning_ship") || !ft_strcmp(title, "3"))
		burning_ship_init(&(*fr));
	else
		fr->func = NULL;
	return (fr);
}

int						main(int argc, char **argv)
{
	t_fractol	*fr;

	if (argc != 2)
		return (return_error(0, 1));
	if ((fr = fractol_init(&(*argv[1]))) == NULL)
		return (return_error(2, 0));
	if ((fr->func) == NULL)
		return (return_error(0, 3));
	redraw(&(*fr));
	mlx_hook(fr->mlx->window, 2, 0, &key_down, &(*fr));
	mlx_hook(fr->mlx->window, 3, 0, &key_up, &(*fr));
	mlx_hook(fr->mlx->window, 4, 0, &mouse_wheel, &(*fr));
	mlx_hook(fr->mlx->window, 6, 0, &mouse_move, &(*fr));
	mlx_loop(fr->mlx->mlx);
}
