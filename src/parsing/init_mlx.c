/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:12:15 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/23 17:36:46 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D.h"

bool	create_images(t_ray *r)
{
	r->minim.xpmh = S_HEIGHT / 6;
	r->minim.xpmw = S_WIDTH / 6;
	r->map.ea.ptr = mlx_xpm_file_to_image(r->mlx, \
		r->map.ea.pto_file, &r->map.ea.xpmw, &r->map.ea.xpmh);
	if (!r->map.ea.ptr)
		return (false);
	r->map.so.ptr = mlx_xpm_file_to_image(r->mlx, \
		r->map.so.pto_file, &r->map.so.xpmw, &r->map.so.xpmh);
	if (!r->map.so.ptr)
		return (false);
	r->map.we.ptr = mlx_xpm_file_to_image(r->mlx, \
		r->map.we.pto_file, &r->map.we.xpmw, &r->map.we.xpmh);
	if (!r->map.we.ptr)
		return (false);
	r->map.no.ptr = mlx_xpm_file_to_image(r->mlx, \
		r->map.no.pto_file, &r->map.no.xpmw, &r->map.no.xpmh);
	if (!r->map.no.ptr)
		return (false);
	r->img.ptr = mlx_new_image(r->mlx, S_WIDTH, S_HEIGHT);
	if (!r->img.ptr)
		return (false);
	r->minim.ptr = mlx_new_image(r->mlx, r->minim.xpmw, r->minim.xpmh);
	if (!r->minim.ptr)
		return (false);
	return (true);
}
