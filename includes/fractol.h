#ifndef FRACTOL_H
#define FRACTOL_H

# include "mlx.h"
# include <libft.h>
# include <stdio.h>
# include <math.h>

/*  Window Settings	*/
# define WIDTH 800
# define HEIGHT 600
# define MAX_ITERATIONS 35

/*  Functions */
# define SQ(x) x * x
# define ABS(x) x < 0 ? -x : x

# define DRAW_COLORED_PIXEL(data, a, n) a ? 						\
	(set_pixel_color(data, x, y, 0x00000000 + 						\
			(n > (MAX_ITERATIONS - 1) / 2 ?							\
			(n * (0x00FF0000 / ((MAX_ITERATIONS - 1) / 2) )) >> 16	\
				:													\
			(n *(0xFF000000 / ((MAX_ITERATIONS - 1) / 2) )) >> 24	\
		)															\
	)) : (set_pixel_color(data, x, y, 0xFFFFFFFF))					\

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buf;
	int		*palette;
	int		color_pattern;
	int		color;
	double	MinIm;
	double	MaxIm;
	double	MinRe;
	double	MaxRe;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double 	Im_factor;
	double	Re_factor;
	char	*fractal_;
	double	x_offset;
	double	y_offset;
	double 	Z_im;
	double	Z_re;
	double	c_re;
	double  c_im;
	int		n;
	double	zim2;
}	t_fractol;

// Events
void	key_close(int n, t_fractol *t);
void	clean_exit(t_fractol *t);
//void	k_hook(int n, t_fractol *f);
//int		hook_mousedown(int button, int x, int y, t_fractol *mlx);

// Initialization
void	clean_init(t_fractol *t);
void	init(t_fractol *t);
int		render(t_fractol *t);

// Draw things
void	draw_line(t_fractol *data, int x1, int y1, int x2, int y2);
void	set_pixel_color(t_fractol *t, int x, int y, int n);

//  Fractals
void	mandelbrot(t_fractol *t);
void	julia(t_fractol *t);
void	newton(t_fractol *t);
void	burning_ship(t_fractol *t);

#endif
