/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:35:22 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/17 16:33:33 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include <math.h>
#include <fractol.h>
#include <keys.h>
#include <stdlib.h>
#include <stdio.h>

int		mouse_event(int k, int x, int y, t_fractol *m);
void	key_hook(int n, t_fractol *f);
int		hook_mousedown(int button, int x, int y, t_fractol *mlx);

int	main(int argc, char **argv)
{	
	t_fractol	*f;

	f = ((t_fractol *) malloc(1 * sizeof(t_fractol)));
	if (argc < 2 || argc > 2)
		return (0);
	init(f);
	f->fractal_ = argv[1];
	/*if (ft_strncmp(argv[1], "mandelbrot", 9) == 0)
		mandelbrot(f);
	if (ft_strncmp(argv[1], "julia", 5) == 0)
		julia(f);
	if (ft_strncmp(argv[1], "newton", 6) == 0)
		newton(f);*/
	render(f);
	mlx_hook(f->win, 2, 1L << 0, key_hook, f);
	mlx_hook(f->win, 4, 1L << 2, hook_mousedown, f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	mlx_loop(f->mlx);
}
