/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/17 15:21:13 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "mlx.h"
# include "cub3D.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

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

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	double	distance_screen;
	t_point	p;
	double	angle_bt_rays;
	double	ray_angle;
	double	p_angle;
	int		color;
	t_img	img;
	int		map_x;
	int		map_y;
}	t_data;

typedef struct s_ray
{
	t_mlx	mlx;
	t_map	map;
	// angle between rays used to draw each pixel column
	double	rayspacing;
	// central ray angle (player)
	double	c_angle;
	// distance from player to screen
	double	d_screen;
	// current ray angle
	double	r_angle;
	int		color;
	t_img	img;
	t_point	p;
	t_co	maplen;
}	t_ray;

// raycasting ----------------

/* raycasting.c */
int		check_collisions(double x, double y, t_ray *map);
int		find_wall(t_ray *rdata, t_point *pt, t_point *step);
double	vertical_intersection(t_ray *rdata);
double	horizontal_intersection(t_ray *rdata);
double	smallest_distance(double hor, double ver, t_ray *rdata);
void	fish_eye(double *distance, int i, t_ray *rdata);
int		raycasting(t_ray *rdata);

/* display.c */
int		init_display(t_ray *rdata);
void	run_game(t_ray *rdata);

/* draw.c */
void	ft_put_pixel(t_img *img, int colomn, int line, int color);
void	draw_column(t_ray *rdata, double distance, int colomn);

/* events.c */
void	move(int keysym, t_ray *rdata);
int		close_win(t_ray *rdata);
int		keys(int keysym, t_ray *rdata);

/* utils.c */
void	clean_display(t_ray *rdata);
double	to_radian(double angle);
double	get_opposite(double adj, double angle);
double	get_adjacent(double opposite, double angle);
double	get_distance(t_point *pt, t_ray *rdata);
void	normalise_angle(double *angle);

#endif