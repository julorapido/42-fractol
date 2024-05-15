/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:42:04 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/15 16:36:29 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fractol.h>
#include <stdlib.h>

void	draw_line(t_fractol *data, int x1, int y1, int x2, int y2)
{
	// y = mx + p
	int	m;
	int	p;

	m = (
		(y2 - y1) 
		/ 
		(x2 - x1)
	);
	p = (m * x1) - y1;

	//t_fractol *e = (t_fractol *) malloc(1 * sizeof(t_fractol));
	//e = data;
	while (x1 < x2)
	{
		int x, y;
		//set_pixel_color(e, 
		x = (m / y1) + p;
		y = (m * x1) + p;
		//	0x00FF0000
		//);

		char	*dst;
		dst = data->buf + (
			((y * data->line_length) + (x * (data->bits_per_pixel / 8)))
		);
		*(unsigned int*)dst = 0x00FF0000;

		x1++;
		y1++;
	}

}

