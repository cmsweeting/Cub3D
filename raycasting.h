/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/03 20:13:40 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <stdlib.h>
# include "minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

// # define EPSILON 0.0001f
# define PI 3.14159265359f
# define CUB 64.0f
# define FOV 60
# define SCREEN_WIDTH 1050
# define SCREEN_HEIGHT 550
# define BLUE 0x112ACD
# define GREEN 0x070E3F
# define BROWN 0x5365D8

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
	float	distance_screen;
	float	P_angle;
	float	ray_angle;
	float	angle_bt_rays;
	t_img	img;
}	t_data;

int		init_display(char **map);
int		raycasting(t_data *data);
void	draw_column(t_data *data, int distance, int colomn);

#endif