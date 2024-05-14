#ifndef FRACTOL_H
#define FRACTOL_H

# include "mlx.h"
//# include "libft.h"
# include <stdio.h>
# include <math.h>

/*  Dimensions	*/
# define WIDTH 900
# define HEIGHT 900
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
}	t_fractol;

// Initialization
void	init(t_fractol *t);
void	render(t_fractol *t);


#endif
