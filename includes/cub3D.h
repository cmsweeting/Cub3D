/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:29:30 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/01 18:20:57 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>

// error_handling ------------

/* error_handling.c */
int	verror(char *s1, char *s2, char *s3);
void	*print_error(int error_code, char *error_message);


#endif 	