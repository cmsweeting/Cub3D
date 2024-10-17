/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:41:42 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/16 18:08:12 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h> // open
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h> // open
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define EP 0.00001
# define PI 3.14159265359
# define CUB 1.0
# define FOV 60
# define S_WIDTH 1050.0
# define S_HEIGHT 550.0
# define SKY 0x112ACD
# define GROUND 0x070E3F
# define WALL_N 0xFF9933 //orange
# define WALL_S 0xFF3399 //pink
# define WALL_W 0x4C0099 //purple
# define WALL_E 0xFFFF00 //yellow

//TODO: determine when + where textures are needed

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	// bits per pixel
	int		bpp;
	int		len;
	int		endian;
}	t_img;


typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
} t_mlx;

typedef struct s_data
{
	double	angle_bt_rays;
	// central ray angle (player)
	double	c_angle;
	double	distance_screen;
	// current ray angle
	double	r_angle;
	int		color;
	t_img	img;
	t_point	p;
}	t_data;

#endif