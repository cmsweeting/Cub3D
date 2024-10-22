/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:08:09 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/22 17:55:01 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static ssize_t	center_mmap(ssize_t window, ssize_t mapsize, int block)
{
	return ((window - ((mapsize + 1) * block)) / 2);
}

static ssize_t	get_min(t_co win_size, t_co map_size)
{
	if (win_size.i / (map_size.i + 1) <= win_size.j / (map_size.j + 1))
		return (win_size.i / (map_size.i + 1));
	return (win_size.j / (map_size.j + 1));
}

bool	build_minimap(t_ray *r)
{
	t_co	map;
	t_co	pix;
	t_co	win_size;
	t_co	start;
	int		block;

	win_size.i = S_HEIGHT / 4;
	win_size.j = S_WIDTH / 4;
	map = (t_co){0};
	block = get_min(win_size, r->map.msize);
	start.j = (center_mmap(win_size.j, r->map.msize.j, block));
	pix.i = 0;
	start.i = (center_mmap(win_size.i, r->map.msize.i, block));
	r->minim.ptr = mlx_new_image(r->mlx, win_size.j, win_size.i);
	if (!r->minim.ptr)
		return (false);
	r->minim.sxpm = mlx_get_data_addr(r->minim.ptr, &r->minim.bpp, &r->minim.len, &r->minim.endian);
	if (!r->minim.sxpm)
		return (false);
	while (pix.i <= win_size.i)
	{
		pix.j = 0;//j;
		start.j = (center_mmap(win_size.j, r->map.msize.j, block));
		map.i = pix.i / block;
		while (pix.j <= win_size.j)
		{
			map.j = pix.j / block;
			if (map.j <= r->map.msize.j && map.i <= r->map.msize.i && r->map.map[map.i][map.j] == '1')
				ft_put_pixel(&r->minim, start.j, start.i, r->map.floor);
			// TODO: fix weird shadow on top
			// else
			// 	ft_put_pixel(&r->minim, start.j, start.i, r->map.ceiling);
			pix.j++;
			start.j++;
		}
		pix.i++;
		start.i++;
	}
	return (true);
}
