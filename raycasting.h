#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <stdlib.h>
# include "minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>

# define PI 3.14f
# define CUB 64
# define FOV (PI / 3)
# define SCREEN_WIDTH 1050
# define SCREEN_HEIGHT 550
# define DISTANCE (SCREEN_WIDTH / 2) / tan(FOV / 2)
# define ANGLE_BT_RAYS (FOV / (SCREEN_WIDTH - 1))
# define BLUE 0x00CCCC
# define GREEN 0x009900
# define BROWN 0x994C00

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
}	t_img;


typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		Px;
	int		Py;
	int		angle;
	t_img	img;
}	t_data;

int		init_display(char **map);
int		raycasting(t_data *data);
void	draw_column(t_data *data, int distance, int colomn);

#endif