/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:12:15 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/21 15:21:58 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D.h"

bool	create_images(t_ray *r)
{
	r->map.ea.ptr = mlx_xpm_file_to_image(r->mlx, \
		r->map.ea.pto_file, &r->map.ea.xpms, &r->map.ea.xpms);
	if (!r->map.ea.ptr)
		return (false);
	r->map.so.ptr = mlx_xpm_file_to_image(r->mlx, \
		r->map.so.pto_file, &r->map.so.xpms, &r->map.so.xpms);
	if (!r->map.so.ptr)
		return (false);
	r->map.we.ptr = mlx_xpm_file_to_image(r->mlx, \
		r->map.we.pto_file, &r->map.we.xpms, &r->map.we.xpms);
	if (!r->map.we.ptr)
		return (false);
	r->map.no.ptr = mlx_xpm_file_to_image(r->mlx, \
		r->map.no.pto_file, &r->map.no.xpms, &r->map.no.xpms);
	if (!r->map.no.ptr)
		return (false);
	r->img.ptr = mlx_new_image(r->mlx, S_WIDTH, S_HEIGHT);
	if (!r->img.ptr)
		return (false);
	return (true);
}
