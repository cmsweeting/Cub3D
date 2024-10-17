/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:12:15 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/17 17:38:10 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D.h"

bool	create_images(t_ray *rdata, t_parser fdata)
{
	int		xpmsize;

	xpmsize = CUB;
	rdata->map.ea.ptr = mlx_xpm_file_to_image(rdata->mlx, fdata.ea.pto_file, \
	&xpmsize, &xpmsize);
	if (!rdata->map.ea.ptr)
		return (false);
	rdata->map.so.ptr = mlx_xpm_file_to_image(rdata->mlx, fdata.so.pto_file, \
	&xpmsize, &xpmsize);
	if (!rdata->map.so.ptr)
		return (false);
	rdata->map.we.ptr = mlx_xpm_file_to_image(rdata->mlx, fdata.we.pto_file, \
	&xpmsize, &xpmsize);
	if (!rdata->map.we.ptr)
		return (false);
	rdata->map.no.ptr = mlx_xpm_file_to_image(rdata->mlx, fdata.no.pto_file, \
	&xpmsize, &xpmsize);
	if (!rdata->map.no.ptr)
		return (false);
	rdata->img.ptr = mlx_new_image(rdata->mlx, S_WIDTH, S_HEIGHT);
	if (!rdata->img.ptr)
		return (false);
	return (true);
}
