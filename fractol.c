/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:35:22 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/15 12:47:57 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include <math.h>
#include <fractol.h>
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
