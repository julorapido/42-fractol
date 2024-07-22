/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:26:40 by jsaintho          #+#    #+#             */
/*   Updated: 2024/07/22 15:21:18 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <libft.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <pthread.h>

/*  Window Settings	*/
# define WIDTH 1280
# define HEIGHT 960
# define MAX_ITERATIONS 30

/* Multi threading */
# define NB_THREADS 4

typedef struct		s_fractol t_fractol;

typedef struct		s_thread
{
	int				id;
	t_fractol		*frctl;
}					t_thread;

typedef struct	mutex_data
{
	t_thread		data[NB_THREADS];
	int				_id_;
	pthread_mutex_t	mutex;
}				mutex_data;

typedef struct		s_render
{
	pthread_t		threads[NB_THREADS];
	//t_thread		args[NB_THREADS];
	mutex_data		mutex_d_;
}					t_render;

struct s_fractol
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
	double		im_factor;
	double		re_factor;
	char		*fractal_;
	double		x_offset;
	double		y_offset;
	double		z_im;
	double		z_re;
	double		c_re;
	double		c_im;
	int			n;
	int			y;
	double		zm;
	double		zm_x;
	double		zim2;
	t_render	render_;
};

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
void	*job(void *arg);

//  Fractals
// void	mandelbrot(t_fractol *t);
// void	*julia(t_thread *t);
// void	burning_ship(t_fractol *t);

#endif
