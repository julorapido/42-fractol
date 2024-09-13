/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:35:22 by jsaintho          #+#    #+#             */
/*   Updated: 2024/09/13 14:47:32 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fractol.h>
#include <mlx.h>
#include <keys.h>
#include <stdlib.h>

int	ft_close(void *p)
{
	t_fractol	*f;

	f = (t_fractol *)(p);
	clean_exit(f);
	return (0);
}

int	main(int argc, char **argv)
{
	int			c;
	t_fractol	*f;

	f = ((t_fractol *) malloc(1 * sizeof(t_fractol)));
	f->julia_im = -0.3842;
	f->julia_re = -0.70176;
	if (!(argc == 2 || argc == 3) || check_params(f, argv, argc) == -1)
	{
		write(1, "Run program : ./fractol <fractal_name> <julia_set>\n", 52);
		write(1, "-Fractals [Julia[1 , 2], Mandelbrot, BurningShip]\n", 51);
		return (free(f), EXIT_FAILURE);
	}
	f->fractal_ = argv[1];
	c = init_render(f);
	if (!c)
	{
		clean_exit(f);
		return (EXIT_FAILURE);
	}
	mlx_key_hook(f->win, k_hook, f);
	mlx_hook(f->win, 4, 1L << 2, hook_mousedown, f);
	mlx_hook(f->win, 17, 0, ft_close, f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	mlx_loop(f->mlx);
	return (0);
}
