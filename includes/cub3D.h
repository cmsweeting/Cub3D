/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:29:30 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/02 13:25:23 by cdomet-d         ###   ########.fr       */
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
#include <sys/stat.h> // open
#include <fcntl.h> // open


# define SUCESS 0
# define ERROR 1

typedef struct s_map
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		fcolor[3];
	int		ccolor[3];
	char	**map;
}	t_map;

// error_handling ------------

/* error_handling.c */
int		verror(char *s1, char *s2, char *s3);
void	*print_error(int error_code, char *error_message);

// parsing -------------------

/* fetch_map.c */
bool	fetch_map(char *arg, t_map *_map);

#endif