/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:30:01 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/23 11:10:05 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	get_xpmstr(t_ray *ray)
{
	ray->map.ea.sxpm = mlx_get_data_addr(ray->map.ea.ptr, &ray->map.ea.bpp, \
	&ray->map.ea.len, &ray->map.ea.endian);
	if (!ray->map.ea.sxpm)
		return (false);
	ray->map.we.sxpm = mlx_get_data_addr(ray->map.we.ptr, &ray->map.we.bpp, \
	&ray->map.we.len, &ray->map.we.endian);
	if (!ray->map.we.sxpm)
		return (false);
	ray->map.so.sxpm = mlx_get_data_addr(ray->map.so.ptr, &ray->map.so.bpp, \
	&ray->map.so.len, &ray->map.so.endian);
	if (!ray->map.so.sxpm)
		return (false);
	ray->map.no.sxpm = mlx_get_data_addr(ray->map.no.ptr, &ray->map.no.bpp, \
	&ray->map.no.len, &ray->map.no.endian);
	if (!ray->map.no.sxpm)
		return (false);
	ray->img.sxpm = mlx_get_data_addr(ray->img.ptr, &ray->img.bpp, \
	&ray->img.len, &ray->img.endian);
	if (!ray->img.sxpm)
		return (false);
	ray->minim.sxpm = mlx_get_data_addr(ray->minim.ptr, &ray->minim.bpp, \
	&ray->minim.len, &ray->minim.endian);
	if (!ray->minim.sxpm)
		return (false);
	return (true);
}
