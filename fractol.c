/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:35:22 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/15 17:52:29 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include <math.h>
#include <fractol.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/*
void	draw_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	//if(x < 0 || y < 0 || y >= WINDOW_HEIGTH || x >= WINDOW_WIDTH)
	//	return ;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));

	dst = data->addr + (offset);
	*(unsigned int*)dst = color;
}*/

int	main(int ac, char **argv)
{
	int	a = ac;
	char **b= argv;
	b++; a++;
	
	t_fractol	*f;

	f = ((t_fractol *) malloc(1 * sizeof(t_fractol)));

	//if (ac < 2)
		//help_msg(&f);
	clean_init(f);
	init(f);
	render(f);
	set_pixel_color(f, 500, 500, 0x00FF00000);
	draw_line(f, 100, 100, 1000, 1000);
	try(f);
	//draw_line(f, 60, 300, 600, 600);
	//draw_line(f, 60, 60, 600, 400);
	// mlx_hook(f.win, EVENT_CLOSE_BTN, 0, end_fractol, &f);
	// mlx_key_hook(f.win, key_event, &f);
	// mlx_mouse_hook(f.win, mouse_event, &f);
	//printf("[mlx window] %dx%d line heigth: %d \n\n\n", WIDTH, HEIGHT, f->line_length);
	//printf("sd");
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	mlx_loop(f->mlx);
	return (0);
}
