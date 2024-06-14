/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:26:40 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/14 16:26:41 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <libft.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>

/*  Window Settings	*/
# define WIDTH 1280
# define HEIGHT 960
# define MAX_ITERATIONS 40

/*  Functions */
/*# define DRAW_COLORED_PIXEL(data, a, n) a ? 					\
	(set_pixel_color(data, x, y, 0x00000000 + 					\
			(n > (MAX_ITERATIONS - 1) / 2 ?						\
			(n * (0x00FF0000 / ((MAX_ITERATIONS - 1) / 2) )) >> 16\
				:												\
			(n *(0xFF000000 / ((MAX_ITERATIONS - 1) / 2) )) >> 24\
		)														\
	)) : (set_pixel_color(data, x, y, 0xFFFFFFFF))				\
*/

typedef struct s_fractol
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*buf;
	int			color;
	double		minim;
	double		maxim;
	double		minre;
	double		maxre;
	int			bpp;
	int			linelen;
	int			endian;
	double		Im_factor;
	double		Re_factor;
	char		*fractal_;
	double		x_offset;
	double		y_offset;
	double	 	Z_im;
	double		Z_re;
	double		c_re;
	double 		c_im;
	int			n;
	int			y;
	double		zm;
	double		zim2;
}	t_fractol;

// Events
void	key_close(int n, t_fractol *t);
int		clean_exit(t_fractol *t);
int		hook_mousedown(int button, int x, int y, t_fractol *mlx);

// MLX & Window
void	clean_init(t_fractol *t);
int		init_render(t_fractol *t);
void	re_render(t_fractol *f);
int		render(t_fractol *t);
int		check_params(char *s);

// Draw funcs
void	set_pixel_color(t_fractol *t, int x, int y, int n);

//  Fractals
void	mandelbrot(t_fractol *t);
void	julia(t_fractol *t);
void	burning_ship(t_fractol *t);

#endif
