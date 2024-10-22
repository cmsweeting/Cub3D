/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:08:09 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/21 17:34:01 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// bool	build_minimap(t_ray *r)
// {
// 	t_co	it;

// 	it.i = r->map.p.i;
// 	it.j = r->map.p.j;
// 	r->minim.ptr = mlx_new_image(r->mlx, (S_WIDTH / 4), (S_HEIGHT / 4));
// 	if (!r->minim.ptr)
// 		return (false);
// 	while (it.i >= 0 && it.i <= r->map.msize.i &&
// it.j >= 0 && it.j <= r->map.msize.j)
// 	{
// 		if (r->map.map[it.i][it.j] == '0');
// 			// mlx_pixel_put
// 	}
// }