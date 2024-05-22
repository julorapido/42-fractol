/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:42:04 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/22 17:57:36 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fractol.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

void mandelbrot(t_fractol *data)
{
	double Re_factor = (data->MaxRe - data->MinRe) / (WIDTH - 1);
	double Im_factor = (data->MaxIm - data->MinIm) / (HEIGHT - 1);

	for(int y = 0; y < HEIGHT; ++y)
	{
    	double c_im = data->MaxIm - y * Im_factor;

    	for(int x = 0; x < WIDTH; ++x)
    	{
			// assign real number 
        	double c_re = data->MinRe + x * Re_factor;
        	double Z_re = c_re, Z_im = c_im;
        	bool isInside = true;
			int n = 0;
        	for(; n < MAX_ITERATIONS; ++n)// max iterations 50 of imaginary number
        	{
				// check if ABS(Zn)
            	if(SQ(Z_re) + SQ(Z_im) > 4)
            	{
                	isInside = false;
                	break;
				}
				double zim2 = SQ(Z_im);
            	Z_im = (2 * Z_re * Z_im) + c_im; // increment it by 2(abi)
            	Z_re = (SQ(Z_re) - zim2) + c_re; // increment it by a² - b²
        	}
			set_pixel_color(data, x, y, isInside, n);
   		}
	}
}



void julia(t_fractol *f)
{
	for(int y = 0; y < HEIGHT; ++y)
	{
    	for(int x = 0; x < WIDTH; ++x)
    	{
        	double Z_re = f->MinRe + x * (f->Re_factor);
			double Z_im = f->MaxIm - y * (f->Im_factor);
        	
			int isInside = 1;
			int n = 0;
        	for(; n < MAX_ITERATIONS; ++n)// max iterations 50 of imaginary number
        	{	
            	if(SQ(Z_re) + SQ(Z_im) > 4)
            	{
                	isInside = 0;
                	break;
            	}
				double zim2 = SQ(Z_im);
            	Z_im = (2 * Z_re * Z_im) - 0.3842;
            	Z_re = (SQ(Z_re) - zim2) - 0.70176;
			}
			//DRAW_COLORED_PIXEL(f, isInside, n);
			set_pixel_color(f, x, y, isInside, n);
   		}
	}
}

void burning_ship(t_fractol *data)
{
	for(int y = 0; y < HEIGHT; ++y)
	{
		double c_im = data->MaxIm - y * data->Im_factor;

    	for(int x = 0; x < WIDTH; ++x)
    	{
        	double c_re = data->MinRe + x * data->Re_factor;
	
			double Z_re = c_re, Z_im = c_im;
        	bool isInside = true;
			int n = 0;
        	for(; n < MAX_ITERATIONS; ++n) 
			{
			 	if(SQ(Z_re) + SQ(Z_im) > 4)
            	{
                	isInside = false;
                	break;
				}

				double zim2 = (Z_re * Z_re) - (Z_im * Z_im);
				// IMAGINARY => 2(abi)
            	Z_im = fabs(2 * Z_re * Z_im) + c_im; // increment it by 2(abi)
				// REAL => a² - b²
            	Z_re = fabs(zim2) + c_re; // increment it by a² - b²
            }
			set_pixel_color(data, x, y, isInside, n);
   		}
	}
}

