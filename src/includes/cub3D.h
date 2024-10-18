/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:26:14 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/18 21:35:49 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "struct.h"
# include <errno.h>
# include <fcntl.h> // open
# include <math.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h> // open
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/X.h>

# define EP 0.00001
# define PI 3.14159265359
# define CUB 64
# define FOV 60
# define S_WIDTH 1900.0
# define S_HEIGHT 1080.0
# define SKY 0x112ACD
# define GROUND 0x070E3F
# define WALL_N 0xFF9933 //orange
# define WALL_S 0xFF3399 //pink
# define WALL_W 0x4C0099 //purple
# define WALL_E 0xFFFF00 //yellow

// error_handling ------------

/* error_handling.c */
int		verror(char *s1, char *s2, char *s3);
void	*perr(int error_code, char *error_message);

// memory_allocation ---------

/* memalloc.c */
bool	ft_realloc(size_t size, char ***arr);
bool	sqalloc_map(t_parser *map);
bool	cpy_fdata(t_parser *map, char **rfile, size_t i);

/* destroy_structs.c */
void	free_fdata(t_parser *map);
void	free_rdata(t_ray *ray);
void	dall(t_ray *ray);

// parsing -------------------

/* extract_file.c */
bool	fill_fdata(char *arg, t_parser *fdata);

/* get_map_data.c */
bool	get_values(t_parser *fdata, char **rfile);

/* handle_colors.c */
bool	rgb_to_int(t_parser *map, char **rgb, bool floor);

/* init_mlx.c */
bool	create_images(t_ray *rdata);

/* is_map_valid.c */
bool	fdata_is_valid(t_parser *map);

/* iterative_floodfill.c */
bool	iwall(t_parser map);

/* init_textures.c */
bool	get_xpmstr(t_ray *ray);

/* p_utils.c */
bool	is_invalid_char(char *str);
bool	is_texture(char *str);
size_t	max_len(char **map);
bool	found_all_elements(t_parser map);
char	*skip_whitespaces(char *str);

/* init_mlx.c */
bool	create_images(t_ray *rdata);

// raycasting ----------------

/* minimap.c */
bool	build_minimap(t_ray *ray);

/* display.c */
void	clean_display(t_ray *rdata);
void	get_angles(t_ray *rdata, t_card pcard);
void	init_data(t_ray *rdata);
int		init_display(t_ray *rdata);
void	run_game(t_ray *rdata);

/* draw.c */
void	ft_put_pixel(t_img *img, int col, int line, int color);
void	draw_column(t_ray *r, double distance, int col);

/* events.c */
void	new_position(t_ray *rdata, double angle);
void	move(t_ray *rdata);
int		close_win(t_ray *rdata);
int		key_press(int keysym, t_ray *rdata);
int		key_release(int keysym, t_ray *rdata);

/* raycasting.c */
int		check_collisions(double x, double y, t_ray *rdata);
int		find_wall(t_ray *rdata, t_point *pt, t_point *step);
double	vertical_intersection(t_ray *rdata);
double	horizontal_intersection(t_ray *rdata);
double	smallest_distance(double hor, double ver, t_ray *rdata);
void	fish_eye(double *distance, int i, t_ray *rdata);
int		raycasting(t_ray *rdata);

/* utils.c */
double	radian(double angle);
double	get_distance(t_point *pt, t_ray *rdata);
void	normalise_angle(double *angle);

// src -----------------------

/* main.c */
int		main(int ac, char *av[]);

/* print_strcts.c */
void	print_parser(t_parser parse);
void	print_ray(t_ray ray);

#endif
