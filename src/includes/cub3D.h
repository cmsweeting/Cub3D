/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:29:30 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/09 14:18:04 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/stat.h> // open
# include <fcntl.h> // open

# define SUCESS 0
# define ERROR 1

typedef struct s_map
{
	unsigned char	allt_found;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	short int		fcolor[3];
	short int		ccolor[3];
	char			**map;
}	t_map;

// error_handling ------------

/* error_handling.c */
int		verror(char *s1, char *s2, char *s3);
void	*print_error(int error_code, char *error_message);

// parsing -------------------

/* extract_file.c */
bool	fetch_map(char *arg, t_map *_map);

/* get_map_data.c */
bool	get_values(t_map *map, char **rfile);

/* p_utils.c */
bool	is_texture(char *str);
bool	cpy_map(t_map *map, char **rfile, size_t i);
char	*skip_whitespaces(char *str);
bool	found_all_elements(t_map map);

/* handle_colors.c */
bool	rgb_to_int(t_map *map, char **rgb, bool floor);

/* ft_realloc.c */
bool	ft_realloc(size_t size, char ***arr);

// src -----------------------

/* main.c */
void	print_map(t_map map);

#endif