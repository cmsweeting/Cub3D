/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:41:42 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/17 17:40:00 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

//TODO: determine when + where textures are needed

typedef struct s_queue
{
	t_co	*item;
	size_t	size;
	size_t	frt;
	size_t	end;
}	t_queue;

typedef enum e_cardinal
{
	NO,
	SO,
	WE,
	EA,
}	t_card;

typedef struct s_img
{
	void			*ptr;
	char			*pto_file;
	char			*strxpm;
	// bits per pixel
	int				bpp;
	int				len;
	int				endian;
}	t_img;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_parser
{
	bool			found_p;
	char			**map;
	short int		ccolor[3];
	short int		fcolor[3];
	t_card			pcard;
	t_co			msize;
	t_co			p;
	t_img			ea;
	t_img			no;
	t_img			so;
	t_img			we;
	unsigned char	allt_found;
}	t_parser;

typedef struct s_ray
{
	void			*mlx;
	void			*win;
	t_parser		map;
	// angle between rays used to draw each pixel column
	double			rayspacing;
	// central ray angle (player)
	double			c_angle;
	// distance from player to screen
	double			d_screen;
	// current ray angle
	double			r_angle;
	int				color;
	t_img			img;
	t_point			p;
}	t_ray;

// error_handling ------------

/* error_handling.c */
int		verror(char *s1, char *s2, char *s3);
void	*print_error(int error_code, char *error_message);

// src -----------------------

/* main.c */
int		main(int ac, char *av[]);

/* print_strcts.c */
void	print_parser(t_parser parse);
void	print_ray(t_ray ray);

#endif