/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:32:30 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/17 16:45:49 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fractol.h>
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
void	set_pixel_color(t_fractol *f, int x, int y, int color)
{
		char	*dst;
		int		offset;

		if(x < 0 || y < 0 || y > HEIGHT || x > WIDTH)
			return ;

		offset = (
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
//  - Initialize fratcal boundaries and factors
//  - Assign f->buf to modify pixel by pixel from it
static void	init_img(t_fractol *f)
{
	f->MinRe = -2.0;
	f->MaxRe = 2.0;
	f->MinIm = -1.2;
	f->MaxIm =  f->MinIm + (f->MaxRe - f->MinRe) * HEIGHT/WIDTH;
	f->Re_factor = (f->MaxRe - f->MinRe) / (WIDTH - 1);
	f->Im_factor = (f->MaxIm - f->MinIm) / (HEIGHT - 1);

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

	init_img(f);
	printf("[mlx window] %dx%d lineLength=%d  buf=%p  bpp=%d \n\n\n", WIDTH, HEIGHT, f->line_length, f->buf, f->bits_per_pixel);
	// get_complex_layout(f);
}
// http://warp.povusers.org/Mandelbrot/
//	this function displays the MLX image to the window.
void	render(t_fractol *f)
{
	if (ft_strncmp(f->fractal_, "mandelbrot", 10) == 0)
		mandelbrot(f);
	if (ft_strncmp(f->fractal_, "julia", 5) == 0)
		julia(f);
	if (ft_strncmp(f->fractal_, "newton", 6) == 0)
		newton(f);
	if (ft_strncmp(f->fractal_, "burningship", 11) == 0)
		burning_ship(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
