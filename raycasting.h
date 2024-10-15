/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/14 18:17:28 by csweetin         ###   ########.fr       */
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

# define EPSILON 0.00001f
# define PI 3.14159265359f
# define CUB /*64.0f/*/1.0f
# define FOV 60
# define SCREEN_WIDTH 1050.0f
# define SCREEN_HEIGHT 550.0f
# define SKY 0x112ACD
# define GROUND 0x070E3F
// # define WALL
# define WALL_N 0xFF9933 //orange
# define WALL_S 0xFF3399 //pink
# define WALL_W 0x4C0099 //purple
# define WALL_E 0xFFFF00 //yellow

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
}	t_img;

typedef struct s_point
{
	double	distX;
	double	distY;
}	t_point;


typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	double	Px;
	double	Py;
	double	distance_screen;
	double	ray_angle;
	double	angle_bt_rays;
	double	dir_ray;
	int		color;
	t_img	img;
	bool	left;
	double	P_angle;
}	t_data;

int		init_display(char **map);
int		raycasting(t_data *data);
void	draw_column(t_data *data, double distance, int colomn);
void	clean_display(t_data *data);
int		close_win(t_data *data);
int		keys(int keysym, t_data *data);
double	to_radian(double angle);
double	get_opposite(double adj, double angle);
double	get_adjacent(double opposite, double angle);
void	leftmost_angle(t_data *data);
int		get_quarter(t_data *data);
double	get_distance(t_point *pt, t_data *data);
int		on_axis(float angle);

#endif