/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:12:15 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/18 21:31:00 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D.h"

bool	create_images(t_ray *rdata)
{
	rdata->map.ea.ptr = mlx_xpm_file_to_image(rdata->mlx, \
		rdata->map.ea.pto_file, &rdata->map.ea.xpms, &rdata->map.ea.xpms);
	if (!rdata->map.ea.ptr)
		return (false);
	rdata->map.so.ptr = mlx_xpm_file_to_image(rdata->mlx, \
		rdata->map.so.pto_file, &rdata->map.so.xpms, &rdata->map.so.xpms);
	if (!rdata->map.so.ptr)
		return (false);
	rdata->map.we.ptr = mlx_xpm_file_to_image(rdata->mlx, \
		rdata->map.we.pto_file, &rdata->map.we.xpms, &rdata->map.we.xpms);
	if (!rdata->map.we.ptr)
		return (false);
	rdata->map.no.ptr = mlx_xpm_file_to_image(rdata->mlx, \
		rdata->map.no.pto_file, &rdata->map.no.xpms, &rdata->map.no.xpms);
	if (!rdata->map.no.ptr)
		return (false);
	rdata->img.ptr = mlx_new_image(rdata->mlx, S_WIDTH, S_HEIGHT);
	if (!rdata->img.ptr)
		return (false);
	return (true);
}
