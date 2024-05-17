#ifndef FRACTOL_H
#define FRACTOL_H

# include "mlx.h"
# include <libft.h>
# include <stdio.h>
# include <math.h>

/*  Window Settings	*/
# define WIDTH 800
# define HEIGHT 600
# define MAX_ITERATIONS 50

/*  Functions */
# define SQ(x) x * x
# define ABS(x) x < 0 ? -x : x

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
}	t_fractol;

//int ft_strncmp(char *str1, char *str2);

// Events
void	key_close(int n, t_fractol *t);
//void	hook_mousedown(int btn, int x, int y, t_fractol *f);

// Initialization
void	clean_init(t_fractol *t);
void	init(t_fractol *t);
void	render(t_fractol *t);

// Draw things
void	draw_line(t_fractol *data, int x1, int y1, int x2, int y2);
void	set_pixel_color(t_fractol *t, int x, int y, int color);

//  Fractals
void	mandelbrot(t_fractol *t);
void	julia(t_fractol *t);
void	newton(t_fractol *t);

#endif
