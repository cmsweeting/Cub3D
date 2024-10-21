/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:26:14 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/21 11:22:07 by cdomet-d         ###   ########.fr       */
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
// masks the 8 lowest bytes of a RGB component
# define EBYTES 0xff
# define S_WIDTH 1050.0
# define S_HEIGHT 550.0
# define SKY 0x112ACD
# define GROUND 0x070E3F

// error_handling ------------

/* error_handling.c */
int		verror(char *s1, char *s2, char *s3);
void	*perr(int error_code, char *error_message);

// memory_allocation ---------

/* memalloc.c */
bool	ft_realloc(size_t size, char ***arr);
bool	sqalloc_map(t_parser *map);
bool	cpy_f(t_parser *map, char **rfile, size_t i);

/* destroy_structs.c */
void	free_f(t_parser *map);
void	free_r(t_ray *ray);
void	dall(t_ray *ray);

// parsing -------------------

/* extract_file.c */
bool	fill_f(char *arg, t_parser *f);

/* get_map_data.c */
bool	get_values(t_parser *f, char **rfile);

/* handle_colors.c */
unsigned long int_to_hex(short int color[3]);
bool	rgb_to_int(t_parser *map, char **rgb, bool floor);

/* init_mlx.c */
bool	create_images(t_ray *r);

/* is_map_valid.c */
bool	f_is_valid(t_parser *map);

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
bool	create_images(t_ray *r);

// raycasting ----------------

/* minimap.c */
// bool	build_minimap(t_ray *ray);

/* display.c */
void	clean_display(t_ray *r);
int		init_display(t_ray *r);
void	run_game(t_ray *r);

/* draw.c */
void	draw_column(t_ray *r, double distance, int col);

/* events.c */
void	move(t_ray *r);
int		close_win(t_ray *r);
int		key_press(int keysym, t_ray *r);
int		key_release(int keysym, t_ray *r);

/* raycasting.c */
int		raycasting(t_ray *r);

/* utils.c */
double	radian(double angle);
double	get_distance(t_point *pt, t_ray *r);
void	normalise_angle(double *angle);
int		check_collisions(double x, double y, t_ray *r);
int		find_wall(t_ray *r, t_point *pt, t_point *step);

// src -----------------------

/* main.c */
int		main(int ac, char *av[]);

/* print_strcts.c */
void	print_parser(t_parser parse);
void	print_ray(t_ray ray);

#endif
