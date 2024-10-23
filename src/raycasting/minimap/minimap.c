/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:08:09 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/23 15:03:27 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static ssize_t	center_mmap(ssize_t window, ssize_t mapsize, int block)
{
	return ((window - ((mapsize + 1) * block)) / 2);
}

static ssize_t	get_min(int width, int height, t_co map_size)
{
	if (height / (map_size.i + 1) <= width / (map_size.j + 1))
		return (height / (map_size.i + 1));
	return (width / (map_size.j + 1));
}

void	clear_player(t_ray *r, t_co offset)
{
	t_co	pix;
	t_co	end;
	int		block;

	block = get_min(r->minim.xpmw, r->minim.xpmh, r->map.msize);
	pix.i = (r->prev_p.y * block) + offset.i;
	end.i = ((r->prev_p.y + 1) * block) + offset.i;
	end.j = ((r->prev_p.x + 1) * block) + offset.j;
	while (pix.i > 0 && pix.i++ < end.i)
	{
		pix.j = (r->prev_p.x * block) + offset.j;
		while (pix.j > 0 && pix.j++ < end.j)
			ft_put_pixel(&r->minim, pix.j, pix.i, ERASE);
	}
}

void	place_player(t_ray	*r)
{
	t_co	pix;
	t_co	end;
	t_co	offset;
	int		block;

	block = get_min(r->minim.xpmw, r->minim.xpmh, r->map.msize);
	offset.i = center_mmap(r->minim.xpmh, r->map.msize.i, block);
	offset.j = center_mmap(r->minim.xpmw, r->map.msize.j, block);
	clear_player(r, offset);
	r->prev_p.x = r->p.x;
	r->prev_p.y = r->p.y;
	pix.i = (r->p.y * block) + offset.i;
	end.i = ((r->p.y + 1) * block) + offset.i;
	end.j = ((r->p.x + 1) * block) + offset.j;
	while (pix.i > 0 && pix.i++ < end.i)
	{
		pix.j = (r->p.x * block) + offset.j;
		while (pix.j > 0 && pix.j++ < end.j)
			ft_put_pixel(&r->minim, pix.j, pix.i, PLAYER);
	}
}

bool	build_minimap(t_ray *r)
{
	t_co	map;
	t_co	pix;
	t_co	draw_it;
	int		block;

	map = (t_co){0};
	block = get_min(r->minim.xpmw, r->minim.xpmh, r->map.msize);
	draw_it.i = (center_mmap(r->minim.xpmh, r->map.msize.i, block));
	pix.i = 0;
	while (pix.i++ <= r->minim.xpmh)
	{
		pix.j = 0;
		draw_it.j = (center_mmap(r->minim.xpmw, r->map.msize.j, block));
		map.i = pix.i / block;
		while (pix.j++ <= r->minim.xpmw)
		{
			map.j = pix.j / block;
			if (map.j <= r->map.msize.j && map.i <= r->map.msize.i && \
			r->map.map[map.i][map.j] == '1')
				ft_put_pixel(&r->minim, draw_it.j, draw_it.i, MMAP);
			draw_it.j++;
		}
		draw_it.i++;
	}
	return (true);
}
