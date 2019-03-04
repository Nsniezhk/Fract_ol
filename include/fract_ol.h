/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsniezhk <nsniezhk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:18:56 by nsniezhk          #+#    #+#             */
/*   Updated: 2018/10/08 17:18:57 by nsniezhk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define THREADS 12

typedef	int			(t_func) ();

typedef	struct		s_control
{
	double			x;
	double			y;
	double			jx;
	double			jy;
	int				key;
	int				mouse_lock;
}					t_control;

typedef	struct		s_image
{
	void			*image;
	char			*ptr;
	int				bpp;
	int				stride;
	int				endian;
}					t_image;

typedef	struct		s_mlx
{
	void			*mlx;
	void			*window;
	t_image			*img;
}					t_mlx;

typedef	struct		s_complex
{
	double			real;
	double			imagine;
}					t_complex;

typedef	struct		s_fractol
{
	t_complex		*max;
	t_complex		*min;
	t_control		*inp;
	t_mlx			*mlx;
	t_func			*func;
	int				depth;
	int				thread;
	int				step;
}					t_fractol;

/*
**							FRACTAL SETS
*/
int					calculate_julia(t_fractol *fr, int x, int y);
int					calculate_mandelbrot(t_fractol *fr, int x, int y);
int					burning_ship(t_fractol *fr, int x, int y);

/*
**							FRACTAL_DATA_INIT
*/
void				mandelbrot_init(t_fractol *fr);
void				julia_init(t_fractol *fr);
void				burning_ship_init(t_fractol *fr);

/*
**							CONTROL
*/

int					key_down(int key, t_fractol *fr);
int					key_up(int key, t_fractol *fr);
int					mouse_wheel(int button, int x, int y, t_fractol *fr);
int					mouse_move(int x, int y, t_fractol *fr);

/*
**							GRAPHICS
*/

void				redraw(t_fractol *fr);

#endif
