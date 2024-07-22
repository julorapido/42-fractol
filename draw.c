/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:42:04 by jsaintho          #+#    #+#             */
/*   Updated: 2024/07/22 17:07:28 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>
//  ty : http://warp.povusers.org/Mandelbrot/
//  ---------------------------------------
//  Mandelbrot set is a set complex numbers
//  ---------------------------------------
//  Complex numbers are 2-dimensional. They consist of two parts: 
//		- The real part (the one without the i coefficient)
//  	- The imaginary part (the one with the i coefficient). 
//  In mathematics complex numbers are drawn in a cartesian coordinate system :
//		- x-axis represents the real part of the number 
//   	- y-axis represents the imaginary part 
//  (eg. the number 1+2i will be a point which x-coord is 1 and y-coord 2)
//  This is exactly the Mandelbrot set.
//  We just are drawing complex numbers on a 2D cartesian coordinate system:
//  If c belongs to the set, we draw a point at the respective location, 
//  else we don't (or we use another color). 
//  Zo = c
//  Zn+1 = Z2n + c
// ==============================================================
// 						CORNER ATTRIBUTIONS
// ==============================================================
// - Define Min && Max real parts of the complex number
// - (left border of the image) is -2.0 && the max (the right border) is 1.0.
// - real part of the complex numbers will go from -2.0 to 1.0
// - lower border of image is equivalent to the imaginary part -1.2
// - max imaginary depends on window size to prevent from image getting stretch
//double MinRe = -2.0; // MIN REA
//double MaxRe = 1.0; // MAX REAL
//double MinIm = -1.2; // MIN IMAGINARY
//double MaxIm = MinIm + (MaxRe-MinRe) * HEIGHT/WIDTH; // MAX IMAGINARY
// =============================================================
//  Assuming window goes from (0, 0) to (Width - 1, Height - 1)
//  ============================================================
//  GET EQUIVALENT COMPLEX NUMBER OF SPECIFIC COORDINATE [x, y]:
//  ============================================================
//  	c_re = MinRe + x * (MaxRe-MinRe) / (WindowWidth - 1);
//		c_im = MaxIm - y * (MaxIm-MinIm) / (WIndowHeight - 1);
//  ============================================================
//  Every Loop until MAX_ITERATIONS checks if complex number (c_re + c_im)
//  is greater than Hausdorff dimension exact value assiociated to the fractal
//  -- If (is greater) value will escape the set and go to infinite 

static void	mandelbrot(int thread_id, t_fractol *m)
{
	long	x;

	m->y = (HEIGHT / NB_THREADS) * thread_id;
	while (m->y++ < (HEIGHT / NB_THREADS) * (thread_id + 1))
	{
		m->c_im = (m->maxim - m->y * (m->im_factor)) + m->y_offset;
		x = -1;
		while (x++ < WIDTH)
		{
			m->c_re = (m->minre + x * (m->re_factor)) + m->x_offset;
			m->z_re = m->c_re;
			m->z_im = m->c_im;
			m->n = 0;
			while (m->n < MAX_ITERATIONS)
			{
				if ((m->z_re * m->z_re) + (m->z_im * m->z_im) > 4)
					break ;
				m->zim2 = m->z_im * m->z_im;
				m->z_im = (2 * m->z_re * m->z_im) + m->c_im;
				m->z_re = ((m->z_re * m->z_re) - m->zim2) + m->c_re;
				m->n++;
			}
			set_pixel_color(m, x, m->y, m->n);
		}
	}
}

static void	julia(int thread_id, t_fractol *f)
{
	long	x;

	f->y = (HEIGHT / NB_THREADS) * thread_id;
	while (f->y++ < (HEIGHT / NB_THREADS) * (thread_id + 1))
	{
		x = -1;
		while (x++ < WIDTH)
		{
			f->z_re = f->minre + x * (f->re_factor) + f->x_offset;
			f->z_im = f->maxim - f->y * (f->im_factor) + f->y_offset;
			f->n = 0;
			while (f->n < MAX_ITERATIONS)
			{
				if ((f->z_re * f->z_re) + (f->z_im * f->z_im) > 4)
					break ;
				f->zim2 = f->z_im * f->z_im;
				f->z_im = (2 * f->z_re * f->z_im) - 0.3842;
				f->z_re = ((f->z_re * f->z_re) - f->zim2) - 0.70176;
				f->n++;
			}
			set_pixel_color(f, x, f->y, f->n);
		}
	}	
}

static void	burning_ship(int thread_id, t_fractol *m)
{
	long	x;

	m->y = (HEIGHT / NB_THREADS) * thread_id;
	while (m->y++ < (HEIGHT / NB_THREADS) * (thread_id + 1))
	{
		m->c_im = (m->maxim - m->y * (m->im_factor)) + m->y_offset;
		x = -1;
		while (x++ < WIDTH)
		{
			m->c_re = (m->minre + x * (m->re_factor)) + m->x_offset;
			m->z_re = (m->c_re);
			m->z_im = (m->c_im);
			m->n = 0;
			while (m->n < MAX_ITERATIONS)
			{
				if ((m->z_re * m->z_re) + (m->z_im * m->z_im) > 4)
					break ;
				m->zim2 = (m->z_im * m->z_im);
				m->z_im = fabsl((2 * m->z_re * m->z_im) + m->c_im);
				m->z_re = fabsl(((m->z_re * m->z_re) - m->zim2) + m->c_re);
				m->n++;
			}
			set_pixel_color(m, x, m->y, m->n);
		}
	}
}

void	*job(void *arg)
{
	t_mutex_data	*md;
	t_fractol	*f;

	md = (t_mutex_data *) arg;
	f = (md->data[(*md)._id_]).frctl;
	pthread_mutex_lock(&(*md).mutex);
	if (f->f_mode == 2)
		julia((md->data[(*md)._id_]).id, (md->data[(*md)._id_]).frctl);
	if (f->f_mode == 1)
		mandelbrot((md->data[(*md)._id_]).id, (md->data[(*md)._id_]).frctl);
	if (f->f_mode == 3)
		burning_ship(md->data[(*md)._id_].id, (md->data[(*md)._id_]).frctl);
	(*md)._id_++;
	pthread_mutex_unlock(&(*md).mutex);
	pthread_exit(NULL);
}
