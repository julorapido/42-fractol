/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:42:45 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/23 16:01:10 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
#include "keys.h"
#include <stdlib.h>
#include <mlx.h>
#include <stdio.h>
// =================================
// 			  KEYBOARD
// =================================
int	k_hook(int k_code, t_fractol *f)
{
	if (k_code == K_ESC)
		clean_exit(f);
	else
	{
		if (k_code == K_UP)
			f->y_offset += (2 * f->Re_factor) * (WIDTH / HEIGHT);
		if (k_code == K_DOWN)
			f->y_offset -= (2 * f->Re_factor) * (WIDTH / HEIGHT);
		if (k_code == K_LEFT)
			f->x_offset -= (2 * f->Re_factor) * (WIDTH / HEIGHT);
		if (k_code == K_RIGHT)
			f->x_offset += (2 * f->Re_factor) * (WIDTH / HEIGHT);
		render(f);
	}
	return 0;
}

// =================================
//				ZOOM
// =================================
void	zoom(int x, int y, t_fractol *f, double zoom)
{
	double	center_re;
	double	center_im;

	center_re = f->MinRe - f->MaxRe;
	center_im = f->MaxIm - f->MinIm;
	f->MaxRe += (center_re - zoom * center_re) / 2;
	f->MinRe = f->MaxRe + zoom * center_re;
	f->MinIm += (center_im - zoom * center_im) / 2;
	f->MaxIm = f->MinIm + zoom * center_im;

	if (x > WIDTH || y > HEIGHT)
		return ;
	
	y -= HEIGHT / 2;
	x -= WIDTH / 2;
	f->y_offset -= (0.01 * (y * 0.01) * (WIDTH / HEIGHT));
	if (zoom > 0)
		f->x_offset += (0.01 * (x * 0.01) * (WIDTH / HEIGHT));
	else 
		f->x_offset -= (0.01 * (x * 0.01) * (WIDTH / HEIGHT));
}
// ==================================
//          MOUSE BUTTON DOWN
// ==================================
int		hook_mousedown(int button, int x, int y, t_fractol *f)
{
	if (button == 4)
		zoom(x, y, f, 0.98);
	else if (button == 5)
		zoom(x, y, f, 1 / 0.98);
	f->Re_factor = (f->MaxRe - f->MinRe) / (WIDTH - 1);
	f->Im_factor = (f->MaxIm - f->MinIm) / (HEIGHT - 1);
	render(f);
	return (0);
}
// =================================
//             CLEAN EXIT
// =================================
void	clean_exit(t_fractol *f)
{
	if(f->img)
	{
		mlx_destroy_image(f->mlx, f->img);
	}	
	if (f->mlx && f->win)
	{
		mlx_loop_end(f->mlx);
		mlx_destroy_window(f->mlx, f->win);
		free(f);
	}
}
