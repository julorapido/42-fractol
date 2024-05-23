/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:42:04 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/23 15:55:16 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fractol.h>
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
//  This is exactly the Mandelbrot set. We just are drawing complex numbers on a 2D cartesian coordinate system:
//  If c belongs to the set, we draw a point at the respective location, 
//  else we don't (or we use another color). 
//  Zo = c
//  Zn+1 = Z2n + c
// ==============================================================
// 						CORNER ATTRIBUTIONS
// ==============================================================
// - Define Min && Max real parts of the complex number
// - (left border of the image) is -2.0 && the maximum (the right border) is 1.0.
// - real part of the complex numbers will go from -2.0 to 1.0
// - lower border of image is equivalent to the imaginary part -1.2 AKA : MIN IMAGINARY	
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

void mandelbrot(t_fractol *m)
{
	int	y;
	int	x;

	y = -1;
	while(y++ < HEIGHT)
	{
    	m->c_im = (m->MaxIm - y * (m->Im_factor)) + m->y_offset;
    	x = 0;
		while (x < WIDTH)
		{
        	m->c_re = (m->MinRe + x * (m->Re_factor)) + m->x_offset;
			m->Z_re = m->c_re;
			m->Z_im = m->c_im;
			m->n = -1;
        	while(m->n++ < MAX_ITERATIONS)
        	{
            	if(SQ(m->Z_re) + SQ(m->Z_im) > 4)
            		break;
				m->zim2 = SQ(m->Z_im);
            	m->Z_im = (2 * m->Z_re * m->Z_im) + m->c_im; // increment it by 2(abi)
            	m->Z_re = (SQ(m->Z_re) - m->zim2) + m->c_re; // increment it by a² - b²
        	}
			set_pixel_color(m, x, y, m->n);
			x++;
   		}
	}
}


void julia(t_fractol *f)
{
	int	y;
	int	x;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
    	while(x < WIDTH)
    	{
        	f->Z_re = f->MinRe + x * (f->Re_factor) + f->x_offset;
			f->Z_im = f->MaxIm - y * (f->Im_factor) + f->y_offset;
			f->n = 0;
			while (f->n < MAX_ITERATIONS)
			{
        		if (SQ(f->Z_re) + SQ(f->Z_im) > 4)
        			break;
				f->zim2 = SQ(f->Z_im);
            	f->Z_im = (2 * f->Z_re * f->Z_im) - 0.3842;
            	f->Z_re = (SQ(f->Z_re) - f->zim2) - 0.70176;
				f->n++;
			}
			set_pixel_color(f, x, y, f->n);
			x++;
   		}
		y++;
	}
}

void burning_ship(t_fractol *data)
{
	/*for(int y = 0; y < HEIGHT; ++y)
	{
		double c_im = data->MaxIm - y * data->Im_factor;

    	for(int x = 0; x < WIDTH; ++x)
    	{
        	double c_re = data->MinRe + x * data->Re_factor;
	
			double Z_re = c_re, Z_im = c_im;
			int n = 0;
        	for(; n < MAX_ITERATIONS; ++n) 
			{
			 	if(SQ(Z_re) + SQ(Z_im) > 4)
                	break;
				double zim2 = (Z_im);
				// IMAGINARY => 2(abi)
            	Z_im = fabs(Z_im * Z_im) + c_im; // increment it by 2(abi)
				// REAL => a² - b²
            	Z_re = fabs(zim2) + c_re; // increment it by a² - b²
            }
			set_pixel_color(data, x, y, n);
   		}
	}*/
}

