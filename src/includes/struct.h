/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:41:42 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/21 15:21:18 by cdomet-d         ###   ########.fr       */
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
	// ptr to xpm
	void			*ptr;
	// path to file
	char			*pto_file;
	// texture size
	int				xpms;
	// char * containing xpm data
	char			*sxpm;
	// bits per pixel
	int				bpp;
	// lenght of the (char *) sxpm
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
	unsigned long	ceiling;
	unsigned long	floor;
	t_card			pcard;
	t_co			msize;
	t_co			p;
	t_img			ea;
	t_img			no;
	t_img			so;
	t_img			we;
	unsigned char	allt_found;
}	t_parser;

typedef struct s_moves
{
	bool			up;
	bool			down;
	bool			left;
	bool			right;
	bool			lturn;
	bool			rturn;
}	t_moves;

// values used to draw the textures in the window
typedef struct s_draw
{
	// vertical iterator
	int	cur_col;
	// wall perceived height
	int	p_height;
	// half-screen height
	int	hs_height;
	// wall half perceived height
	int	hp_height;
	// used to see if the top of the wall is visible or not
	int	wall_top;
}	t_draw;

// coordinates used to move in char * sxpm
typedef struct t_drawco
{
	// current column being drawn
	int		col;
	// line in which to get pixel in xpmstr
	double	line;
	// line incrementer
	double	line_it;
}	t_draw_co;

typedef struct s_minimap
{
}	t_mmap;

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
	t_img			cwall;
	t_img			img;
	t_img			minim;
	t_moves			moves;
	t_point			hhitpt;
	t_point			p;
	t_point			vhitpt;
	double			i;
}	t_ray;

// error_handling ------------

/* error_handling.c */
int		verror(char *s1, char *s2, char *s3);
void	*perr(int error_code, char *error_message);

// src -----------------------

/* main.c */
int		main(int ac, char *av[]);

/* print_strcts.c */
void	print_parser(t_parser parse);
void	print_ray(t_ray ray);

#endif
