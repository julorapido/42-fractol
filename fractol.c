/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:35:22 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/14 15:51:29 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fractol.h>
#include <mlx.h>
#include <keys.h>
#include <stdlib.h>

void	k_hook(int n, t_fractol *f);

int	ft_close(void)
{
	exit(0);
}

int	main(int argc, char **argv)
{
	int			c;
	t_fractol	*f;

	f = ((t_fractol *) malloc(1 * sizeof(t_fractol)));
	if (argc < 2 || argc > 2 || check_params(argv[1]) == -1)
	{
		write(1, "Please Run the program with the Fractal Set Name\n", 50);
		write(1, "Sets available : [Julia, Mandelbrot, BurningShip]\n", 51);
		return (0);
	}
	f->fractal_ = argv[1];
	c = init_render(f);
	if (!c)
	{
		clean_exit(f);
		return (0);
	}
	mlx_hook(f->win, 2, 1L << 0, k_hook, f);
	mlx_hook(f->win, 4, 1L << 2, hook_mousedown, f);
	mlx_hook(f->win, 17, 0, ft_close, 0);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	mlx_loop(f->mlx);
	return (0);
}
