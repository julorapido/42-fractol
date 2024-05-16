/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:42:04 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/16 16:01:54 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fractol.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define SQ(x) x*x

void	draw_line(t_fractol *data, int x1, int y1, int x2, int y2)
{
	// y = mx + p
	int	m;
	int	p;

	m = (
		(y2 - y1) 
		/  (x2 - x1)
	);
	p = y1 - (m * x1);
	while (x1 < x2)
	{
		//printf("%d %d \n", ((m / y1) + p), ((m * x1) + p));
		set_pixel_color(data, 
			((m / y1) + p), ((m * x1) + p),
			0x00FF0000
		);
		x1++;
		y1++;
	}

}
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
void try(t_fractol *data)
{
	// ==============================================================
	// 						CORNER ATTRIBUTIONS
	// ==============================================================
	// - Define Min && Max real parts of the complex number
	// - (left border of the image) is -2.0 && the maximum (the right border) is 1.0.
	// - real part of the complex numbers will go from -2.0 to 1.0
	// - lower border of image is equivalent to the imaginary part -1.2 AKA : MIN IMAGINARY
	// - max imaginary depends on window size to prevent from image getting stretch
	double MinRe = -2.0; // MIN REAL
	double MaxRe = 1.0; // MAX REAL
	double MinIm = -1.2; // MIN IMAGINARY
	double MaxIm = MinIm + (MaxRe-MinRe) * HEIGHT/WIDTH; // MAX IMAGINARY
	// =============================================================

	double Re_factor = (MaxRe-MinRe) / (WIDTH - 1);
	double Im_factor = (MaxIm-MinIm) / (HEIGHT - 1);

	//  Assuming window goes from (0, 0) to (Width - 1, Height - 1)
	//  ============================================================
	//  GET EQUIVALENT COMPLEX NUMBER OF SPECIFIC COORDINATE [x, y]:
	//  ============================================================
	//  	c_re = MinRe + x * (MaxRe-MinRe) / (WindowWidth - 1);
 	//		c_im = MaxIm - y * (MaxIm-MinIm) / (WIndowHeight - 1);
	//  ============================================================
	// Z = Z2 + c 
	// c = c_re + c_im
	// Zn => Zn-1 + c
	// Zn = c_re + c_im * i
	for(int y = 0; y < HEIGHT; ++y)
	{
		// assign imaginary number
    	double c_im = MaxIm - y * Im_factor;

    	for(int x = 0; x < WIDTH; ++x)
    	{
			// assign real number 
        	double c_re = MinRe + x * Re_factor;
			// c is assigned for each pixel
			// then we search through 50 iterations from here
			// to find numbers that are inside the Mandelbrot set
        	double Z_re = c_re, Z_im = c_im;
        	bool isInside = true;
			int n = 0;
        	for(; n < MAX_ITERATIONS; ++n)// max iterations 50 of imaginary number
        	{
				// check if ABS(Zn)
				// c = Z_re + Z_im
            	if(SQ(Z_re) + SQ(Z_im) > 4)
            	{
                	isInside = false;
                	break;
				}
				// z = z² + c 
				// z² + c part of the code:
				// needs to Add two complex numbers
				// (a + bi)² = a² - b² + 2(abi)
				// where a = z² && b = c
				double zim2 = SQ(Z_im);
				// IMAGINARY => 2(abi)
            	Z_im = (2 * Z_re * Z_im) + c_im; // increment it by 2(abi)
				// REAL => a² - b²
            	Z_re = (SQ(Z_re) - zim2) + c_re; // increment it by a² - b²
        	}
        	if(isInside) 
				set_pixel_color(data, x, y, 0x00FF0000);
			else
				set_pixel_color(data, x, y, 0x00000000 + (
						n > (MAX_ITERATIONS - 1) / 2 ? 
						(n * (0x00FF0000 / ((MAX_ITERATIONS - 1) / 2) )) >> 16 
						: 
						(n *(0xFF000000 / ((MAX_ITERATIONS - 1) / 2) )) >> 24
					)
				);
   		}
	}
}



void try_julia(t_fractol *data)
{
	double MinRe = -2.0; // MIN REAL
	double MaxRe = 1.0; // MAX REAL
	double MinIm = -1.2; // MIN IMAGINARY
	double MaxIm = MinIm + (MaxRe-MinRe) * HEIGHT/WIDTH; // MAX IMAGINARY
	double Re_factor = (MaxRe-MinRe) / (WIDTH - 1);
	double Im_factor = (MaxIm-MinIm) / (HEIGHT - 1);

	for(int y = 0; y < HEIGHT; ++y)
	{
		// assign imaginary number
    	double c_im = MaxIm - y * Im_factor;
    	for(int x = 0; x < WIDTH; ++x)
    	{
			// assign real number 
        	double c_re = MinRe + x * Re_factor;
		
        	double Z_re = c_re, Z_im = c_im;
        	bool isInside = true;
        	for(int n = 0; n < 50; ++n)// max iterations 50 of imaginary number
        	{	
            	if(SQ(Z_re) + SQ(Z_im) > 4)
            	{
                	isInside = false;
                	break;
            	}	
				double zim2 = SQ(Z_im);
				Z_im = (2 * Z_re * Z_im) + 0.288; // increment it by 2(abi)
            	Z_re = (SQ(Z_re) - zim2) + 0.288; // increment it by a² - b² 
			}
        	if(isInside) 
				set_pixel_color(data, x, y, 0x00FF0000);
   		}
	}
}
