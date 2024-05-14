/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:32:30 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/14 17:25:32 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fractol.h>


//  ========================================================================
//                                 INIT IMG
//  ========================================================================
//  - Initialize image, palette and buffer
//  - 
static void	init_img(t_fractol *f)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buf;

	f->palette = ft_calloc((MAX_ITERATIONS + 1), sizeof(int));
	
	if (!(f->palette))
		clean_exit(msg("error initializing color scheme.", "", 1), f);

	f->img = mlx_new_image(f->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	if (!(f->img))
		clean_exit(msg("image creation error.", "", 1), f);

	buf = mlx_get_data_addr(f->img, &pixel_bits, &line_bytes, &endian);
	f->buf = buf;
}
//  =====================================================
//   					      INIT
//  =====================================================
//  Creates a new MLX instance, a new window and populates
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

	mlx_clear_window(f->mlx, f->win);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pr = f->min_r + (double)x * (f->max_r - f->min_r) / WIDTH;
			pi = f->max_i + (double)y * (f->min_i - f->max_i) / HEIGHT;
			nb_iter = calculate_fractal(f, pr, pi);
			set_pixel_color(f, x, y, f->palette[nb_iter]);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}



