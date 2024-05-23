/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:35:22 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/23 14:40:04 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fractol.h>
#include <mlx.h>
#include <keys.h>
#include <stdlib.h>

void	k_hook(int n, t_fractol *f);
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
	mlx_hook(f->win, 2, 1L << 0, k_hook, f);
	mlx_hook(f->win, 4, 1L << 2, hook_mousedown, f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	mlx_loop(f->mlx);
}
