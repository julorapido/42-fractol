/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:35:22 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/14 12:54:38 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include <math.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	draw_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));

	dst = data->addr + (offset);
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img_;

	// mlx setup
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FRACTOL");

	// image to write to
	img_.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img_.addr = mlx_get_data_addr(img_.img, &img_.bits_per_pixel, &img_.line_length, &img_.endian);
	
	draw_pixel(&img_, 20, 20, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img_.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
