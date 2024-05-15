#ifndef FRACTOL_H
#define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <math.h>

/*  Window Settings	*/
# define WIDTH 1440
# define HEIGHT 1024
# define MAX_ITERATIONS 60

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buf;
	int		*palette;
	int		color_pattern;
	int		color;
	double	sx;
	double	rx;
	double	fx;
	double	kr;
	double	ki;
	double	min_i;
	double	max_i;
	double	min_r;
	double	max_r;
	int		bits_per_pixel;
	int		line_length;
}	t_fractol;

// Initialization
void	clean_init(t_fractol *t);
void	init(t_fractol *t);
void	render(t_fractol *t);

// Draw things
void	set_pixel_color(t_fractol *t, int x, int y, int color);
void	draw_line(t_fractol *data, int x1, int y1, int x2, int y2);


#endif
