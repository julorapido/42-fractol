/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:32:30 by jsaintho          #+#    #+#             */
/*   Updated: 2024/07/22 16:19:11 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

//  =======================================================================
//                            SET PIXEL COLOR                            
//  ======================================================================
//	The MLX image is composed of 32-bits[INTEGER] Pixels.
//	Form of 0xAARRGGBB. 8 bits encode each color component,
//	Alpha (Transparency), Red, Green and Blue.
//	Bit shifting:
//		- BB >> 0   (0x000000FF)
//		- GG >> 8   (0x0000FF00)
//		- RR >> 16  (0x00FF0000)
//		- AA >> 24  (0xAA000000)
void	set_pixel_color(t_fractol *f, int x, int y, int n)
{
	char	*dst;
	int		offset;
	int		color;
	int		pixel_insideset;

	pixel_insideset = 0;
	if (n == MAX_ITERATIONS)
		pixel_insideset = 1;
	if (x < 0 || y < 0 || y > HEIGHT || x > WIDTH)
		return ;
	if (!pixel_insideset)
	{
		if (n > (MAX_ITERATIONS - 1) / 2)
			color = ((n * (0x00FF0000 / ((MAX_ITERATIONS - 1) / 2))) >> 16);
		else
			color = ((n * (0xFF000000 / ((MAX_ITERATIONS - 1) / 2))) >> 24);
	}
	else
		color = 0xBBBBBBBB;
	offset = (y * f->linelen + x * (f->bpp / 8));
	dst = f->buf + (offset);
	*(unsigned int *)dst = color;
}

//  ========================================================================
//                                 INIT IMG
//  ========================================================================
//  - Initialize image, palette and buffer
//  - Initialize fratcal boundaries and factors
//  - Assign f->buf to modify pixel by pixel from it
static void	init_img(t_fractol *f)
{
	f->minre = -2.0;
	f->maxre = 2.0;
	f->minim = -1.5;
	f->maxim = f->minim + (f->maxre - f->minre) * HEIGHT / WIDTH;
	f->zm = 0.005;
	f->zm_x = 0.01;
	if (ft_strncmp(f->fractal_, "burningship", 11) == 0)
	{
		f->minim = -0.1;
		f->maxim = 0.1;
		f->minre = -1.85;
		f->maxre = -1.65;
		f->zm = 0.0005;
		f->zm_x = 0.001;
	}
	f->re_factor = (f->maxre - f->minre) / (WIDTH - 1);
	f->im_factor = (f->maxim - f->minim) / (HEIGHT - 1);
	f->x_offset = 0;
	f->y_offset = 0;
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!(f->img))
		clean_exit(f);
	f->buf = mlx_get_data_addr(f->img,
			&f->bpp, &f->linelen, &f->endian);
}

//  =====================================================
//   					      INIT
//  =====================================================
//  Creates a new MLX instance, a new window and set
//  the fractol data structure with default values.
int	init_render(t_fractol *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
	{
		clean_exit(f);
		return (-1);
	}
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fractol");
	if (!f->win)
	{
		clean_exit(f);
		return (-1);
	}
	init_img(f);
	re_render(f);
	return (1);
}

//  =====================================================
//   					  RE-RENDER
//  =====================================================
//  Rewrite pixels buffer and re-put image back to MLX Window
void	re_render(t_fractol *f)
{
	int			i;
	t_render	*r;

	i = 0;
	r = &f->render_;
	(f->render_.mutex_d_)._id_ = 0;
	pthread_mutex_init(&((f->render_.mutex_d_).mutex), NULL);
	while (i < NB_THREADS)
	{
		r->mutex_d_.data[i].id = i;
		r->mutex_d_.data[i].frctl = f;
		pthread_create(r->threads + i, NULL, job, &(f->render_.mutex_d_));
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(r->threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&(f->render_.mutex_d_.mutex));
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

// ========================================================
//						CHECK PARAMS
// ========================================================
int	check_params(char *s)
{
	int	v;

	v = 0;
	if (ft_strncmp(s, "mandelbrot", 10) == 0)
		v = 1;
	if (ft_strncmp(s, "julia", 5) == 0)
		v = 1;
	if (ft_strncmp(s, "burningship", 11) == 0)
		v = 1;
	if (v == 0)
		return (-1);
	return (v);
}
