/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:41:42 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/17 14:41:38 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "parsing.h"

# include <errno.h>
# include <fcntl.h> // open
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h> // open
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>


//TODO: determine when + where textures are needed

typedef struct s_img
{
	void	*ptr;
	char	*xpm_data;
	// bits per pixel
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct s_map
{
	char		**map;
	short int	ccolor[3];
	short int	fcolor[3];
	t_card		pcard;
	t_co		p;
	t_img		ea;
	t_img		no;
	t_img		so;
	t_img		we;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

#endif