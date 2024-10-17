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

# define SUCESS 0
# define ERROR 1

// parsing -------------------

/* extract_file.c */
bool	fill_fdata(char *arg, t_parser *fdata);

/* get_map_data.c */
bool	get_values(t_parser *fdata, char **rfile);

/* handle_colors.c */
bool	rgb_to_int(t_parser *fdata, char **rgb, bool floor);

/* iterative_floodfill.c */
bool	iwall(t_parser fdata);

// memory_allocation ---------

/* memalloc.c */
bool	cpy_fdata(t_parser *fdata, char **rfile, size_t i);
bool	ft_realloc(size_t size, char ***arr);
bool	sqalloc_map(t_parser *fdata);
void	free_fdata(t_parser *fdata);

// parsing -------------------

/* p_utils.c */
bool	found_all_elements(t_parser fdata);
bool	is_invalid_char(char *str);
bool	is_texture(char *str);
char	*skip_whitespaces(char *str);
size_t	max_len(char **map);

/* is_map_valid.c */
bool	fdata_is_valid(t_parser *fdata);

#endif