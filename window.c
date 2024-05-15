/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:32:30 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/15 17:30:11 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fractol.h>
#include <stdio.h>
//  =======================================================================
// 								 CLEAN INIT
//  =======================================================================
void clean_init(t_fractol *f)
{
	f->mlx = NULL;
	f->win = NULL;
	f->img = NULL;
	f->buf = NULL;
	// f->set = -1;
	f->min_r = 0;
	f->max_r = 0;
	f->min_i = 0;
	f->max_i = 0;
	f->kr = 0;
	f->ki = 0;
	f->sx = 0;
	f->rx = 0;
	f->fx = 0;
	//f->palette = NULL;
	//f->color_pattern = -1;
	//f->color = 0;
}

//  =======================================================================
//                            SET PIXEL COLOR                            
//  ======================================================================
//	Add a color to one pixel of the MLX image map.
//	The MLX image is composed of 32-bits[INTEGER] Pixels.
//	Form of 0xAARRGGBB. 8 bits encode each color component,
//	Alpha (Transparency), Red, Green and Blue.
//	Bit shifting:
//		- BB >> 0   (0x000000BB)
//		- GG >> 8   (0x0000GG00)
//		- RR >> 16  (0x00RR0000)
//		- AA >> 24  (0xAA000000)
void	set_pixel_color(t_fractol *f, int x, int y, int color)
{
		if (x < 0 || y < 0 || y > HEIGHT || x > WIDTH)
			return ;
		/*
		f->buf[x * 4 + y * WIDTH * 4] = color;
		f->buf[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
		f->buf[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
		f->buf[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
		*/
		char	*dst;
		int		offset;

		//if(x < 0 || y < 0 || y >= WINDOW_HEIGTH || x >= WINDOW_WIDTH)
		//	return ;

		offset =(
				y * f->line_length
				+
				x * (f->bits_per_pixel / 8)
		);
		dst = f->buf + (offset);
		*(unsigned int*)dst = color;
}
//  ========================================================================
//                                 INIT IMG
//  ========================================================================
//  - Initialize image, palette and buffer
//  - Assign f->buf to modify pixel by pixel from it
static void	init_img(t_fractol *f)
{
	//int		pixel_bits;
	//int		line_bytes;
	int		endian;
	char	*buf;

	f->palette = ft_calloc((MAX_ITERATIONS + 1), sizeof(int));
	
	//if (!(f->palette))
	//	clean_exit(msg("error initializing color scheme.", "", 1), f);

	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	//if (!(f->img))
	//	clean_exit(msg("image creation error.", "", 1), f);

	// get data adress FROM the IMAGE
	// so you can write to it
	// and modify pixel by pixe
	f->buf = mlx_get_data_addr(f->img, &f->bits_per_pixel, 
			&f->line_length, &f->endian);
	//f->buf = buf;
}
//  =====================================================
//   					      INIT
//  =====================================================
//  Creates a new MLX instance, a new window and set
//  the fractol data structure with default values.
void	init(t_fractol *f)
{
	f->mlx = mlx_init();
	//if (!f->mlx)
	//	clean_exit(msg("MLX: error connecting to mlx.", "", 1), f);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fractol");
	//if (!f->win)
	//	clean_exit(msg("MLX: error creating window.", "", 1), f);
	f->sx = 2.0;
	f->rx = 0.5;
	f->fx = 1.0;
	init_img(f);
	printf("[mlx window] %dx%d lineLength=%d  buf=%p  bpp=%d \n\n\n", WIDTH, HEIGHT, f->line_length, f->buf, f->bits_per_pixel);
	// get_complex_layout(f);
}
//  =========================================================================
//                                    RENDER
//  =========================================================================
//	- Iterates through each pixel of the window, translates the pixel's
//	coordinates into a complex number to be able to calculate if that number
//	is part of the fractal set or not.
//	- The number of iterations that complex number goes through before being
//	rejected from the fractal set determines which color is applied to the pixel.
//	- Once all pixels have been assessed and added to the MLX image,
//	this function displays the MLX image to the window.
void	render(t_fractol *f)
{
	int		x;
	int		y;
	double	pr;
	double	pi;
	int		nb_iter;

	return;
	mlx_clear_window(f->mlx, f->win);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			//pr = f->min_r + (double)x * (f->max_r - f->min_r) / WIDTH;
			//pi = f->max_i + (double)y * (f->min_i - f->max_i) / HEIGHT;
			//nb_iter = calculate_fractal(f, pr, pi);
			set_pixel_color(f, x, y, 0xFFFFFFAF/*f->palette[nb_iter]*/ );
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
// http://warp.povusers.org/Mandelbrot/
