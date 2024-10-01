#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <stdlib.h>
# include "minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

int	init_display();

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_data;


#endif