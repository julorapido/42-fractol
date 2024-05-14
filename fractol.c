/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:35:22 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/14 17:56:55 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include <math.h>
#include "fractol.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define round(x) x == 0 ? 1 : x

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

	//if(x < 0 || y < 0 || y >= WINDOW_HEIGTH || x >= WINDOW_WIDTH)
	//	return ;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));

	dst = data->addr + (offset);
	*(unsigned int*)dst = color;
}

void	draw_line(t_data *data, int x1, int y1, int x2, int y2)
{
	// y = mx + p
	int	m;
	int	p;

	m = (
		(y2 - y1) == 0 ? 1 : (y2 - y1) 
		/ 
		(x2 - x1) == 0 ? 1 : (x2 - x1)
	);
	p = (m * x1) - y1;
	while (x1 < x2)
	{
		draw_pixel(data, 
			((m / y1) + p), ((m * x1) + p),
			0x00FF0000
		);
		x1++;
		y1++;
	}

}


int	main(int ac)
{
	t_data	img_;

	t_fractol	f;

	//if (ac < 2)
		//help_msg(&f);

	clean_init(&f);
	init(&f);
	render(&f);

	// draw_line(d, 0, 0, 1000, 1000);
	// mlx_hook(f.win, EVENT_CLOSE_BTN, 0, end_fractol, &f);
	// mlx_key_hook(f.win, key_event, &f);
	// mlx_mouse_hook(f.win, mouse_event, &f);

	mlx_loop(f.mlx);
	return (0);
}
