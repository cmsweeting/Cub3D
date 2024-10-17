/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:29:30 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/15 13:48:39 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3D.h"
// # include "libft.h"
// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <string.h>
// # include <stdbool.h>
// # include <errno.h>
// # include <sys/stat.h> // open
// # include <fcntl.h> // open

# define SUCESS 0
# define ERROR 1

typedef enum e_cardinal
{
	NO,
	SO,
	WE,
	EA,
}	t_card;

typedef struct s_queue
{
	t_co	*item;
	size_t	size;
	size_t	frt;
	size_t	end;
}	t_queue;

typedef struct s_parser
{
	t_co			p;
	t_co			msize;
	t_card			pcard;
	bool			found_p;
	unsigned char	allt_found;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	short int		fcolor[3];
	short int		ccolor[3];
	char			**map;
}	t_parser;

// error_handling ------------

/* error_handling.c */
int		verror(char *s1, char *s2, char *s3);
void	*print_error(int error_code, char *error_message);

// parsing -------------------

/* extract_file.c */
bool	fill_struct(char *arg, t_parser *_map);

/* get_parser_data.c */
bool	get_values(t_parser *map, char **rfile);

/* p_utils.c */
bool	is_invalid_char(char *str);
bool	is_texture(char *str);
size_t	max_len(char **map);
bool	found_all_elements(t_parser map);
char	*skip_whitespaces(char *str);

/* handle_colors.c */
bool	rgb_to_int(t_parser *map, char **rgb, bool floor);

/* is_map_valid.c */
bool	map_is_valid(t_parser *map);

// memory_allocation ---------

/* memalloc.c */
bool	ft_realloc(size_t size, char ***arr);
bool	sqalloc_map(t_parser *map);
bool	cpy_map(t_parser *map, char **rfile, size_t i);

// parsing -------------------

/* iterative_floodfill.c */
bool	iwall(t_parser map);

// src -----------------------

/* main.c */
void	print_parser(t_parser map);
int		main(int ac, char *av[]);

#endif