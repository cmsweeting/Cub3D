/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/15 18:29:25 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "mlx.h"
# include "parsing.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

# define EPSILON 0.00001
# define PI 3.14159265359
# define CUB 1.0
# define FOV 60
# define SCREEN_WIDTH 1050.0
# define SCREEN_HEIGHT 550.0
# define SKY 0x112ACD
# define GROUND 0x070E3F
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
	double	X;
	double	Y;
}	t_point;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	double	distance_screen;
	t_point	P;
	double	angle_bt_rays;
	double	ray_angle;
	double	P_angle;
	int		color;
	t_img	img;
	int		map_x;
	int		map_y;
}	t_data;

// raycasting ----------------

/* raycasting.c */
int	check_collisions(double x, double y, t_data *map);
int	find_wall(t_data *data, t_point *pt, t_point *step);
double	vertical_intersection(t_data *data);
double	horizontal_intersection(t_data *data);
double	smallest_distance(double hor, double ver, t_data *data);
void	fish_eye(double *distance, int i, t_data *data);
int	raycasting(t_data *data);

/* display.c */
int	init_display(t_map *map);

/* draw.c */
void	ft_put_pixel(t_img *img, int colomn, int line, int color);
void	draw_column(t_data *data, double distance, int colomn);

/* events.c */
void	step_left(t_data *data, double x, double y);
void	step_right(t_data *data, double x, double y);
void	step_up(t_data *data, double x, double y);
void	step_down(t_data *data, double x, double y);
void	move(int keysym, t_data *data);
int	close_win(t_data *data);
int	keys(int keysym, t_data *data);

/* utils.c */
void	clean_display(t_data *data);
double	to_radian(double angle);
double	get_opposite(double adj, double angle);
double	get_adjacent(double opposite, double angle);
int	get_quarter(t_data *data);
void	leftmost_angle(t_data *data);
double	get_distance(t_point *pt, t_data *data);
int	on_axis(float angle);
void	normalise_angle(double *angle);



#endif