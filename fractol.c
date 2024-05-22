/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:35:22 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/22 17:31:12 by jsaintho         ###   ########.fr       */
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
	int	c;
	t_fractol	*f;

	f = ((t_fractol *) malloc(1 * sizeof(t_fractol)));
	if (argc < 2 || argc > 2)
		return (0);
	init(f);
	f->fractal_ = argv[1];
	c = render(f);
	if (!c)
	{
		clean_exit(f);
		return (0);
	}
	mlx_hook(f->win, 2, 1L << 0, key_hook, f);
	mlx_hook(f->win, 4, 1L << 2, hook_mousedown, f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	mlx_loop(f->mlx);
}
