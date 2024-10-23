/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:08:09 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/23 17:39:46 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static ssize_t	center_mmap(ssize_t window, ssize_t mapsize, int block)
{
	return ((window - ((mapsize + 1) * block)) / 2);
}

static double	get_min(int width, int height, t_co map_size)
{
	if (height / ((double)map_size.i + 1) <= width / ((double)map_size.j + 1))
		return (height / ((double)map_size.i + 1));
	return (width / ((double)map_size.j + 1));
}

void	draw_line(t_ray *r)
{
	t_point	delta;
	t_point	pix;
	int		step;
	
	delta.y = (int)r->shitpt.y - (int)r->p.y;
	delta.x = (int)r->shitpt.x - (int)r->p.x;
	step = (delta.y * 2) - delta.x;
	pix.y = r->p.y * get_min(r->minim.xpmw, r->minim.xpmh, r->map.msize);
	pix.x = r->p.x * get_min(r->minim.xpmw, r->minim.xpmh, r->map.msize);
	while (delta.x <= pix.x)
	{
		if (step < 0)
		{
			step += delta.x * 2;
			ft_put_pixel(&r->minim, delta.x, delta.y, PLAYER);
		}
		else
		{
			delta.x++;
			step += delta.x * 2;
			ft_put_pixel(&r->minim, delta.x, delta.y, PLAYER);
		}
		delta.x++;
	}
}

void	clear_player(t_ray *r, t_point offset)
{
	t_point	pix;
	t_point	end;
	int		block;

	block = get_min(r->minim.xpmw, r->minim.xpmh, r->map.msize);
	pix.y = (r->prev_p.y * block) + offset.y;
	end.y = ((r->prev_p.y + 1) * block) + offset.y;
	end.x = ((r->prev_p.x + 1) * block) + offset.x;
	while (pix.y > 0 && pix.y++ < end.y)
	{
		pix.x = (r->prev_p.x * block) + offset.x;
		while (pix.x > 0 && pix.x++ < end.x)
			ft_put_pixel(&r->minim, pix.x, pix.y, ERASE);
	}
}

void	place_player(t_ray	*r)
{
	t_point	pix;
	t_point	end;
	t_point	offset;
	double	block;

	block = get_min((double)r->minim.xpmw, (double)r->minim.xpmh, r->map.msize);
	offset.y = center_mmap(r->minim.xpmh, r->map.msize.i, block);
	offset.x = center_mmap(r->minim.xpmw, r->map.msize.j, block);
	clear_player(r, offset);
	r->prev_p.x = r->p.x;
	r->prev_p.y = r->p.y;
	pix.y = (r->p.y * block) + offset.y;
	end.y = ((r->p.y + 1) * block) + offset.y;
	end.x = ((r->p.x + 1) * block) + offset.x;
	while (pix.y > 0 && pix.y++ < end.y)
	{
		pix.x = (r->p.x * block) + offset.x;
		while (pix.x > 0 && pix.x++ < end.x)
			ft_put_pixel(&r->minim, pix.x, pix.y, PLAYER);
	}
}

bool	build_minimap(t_ray *r)
{
	t_co	map;
	t_point	pix;
	t_point	draw_it;
	double	block;

	map = (t_co){0};
	//TODO: find a way to protect when block is too small to draw;
	block = get_min(r->minim.xpmw, r->minim.xpmh, r->map.msize);
	if (block <= 0);
		return (false);
	draw_it.y = (center_mmap(r->minim.xpmh, r->map.msize.i, block));
	pix.y = 0;
	while (pix.y++ <= r->minim.xpmh)
	{
		pix.x = 0;
		draw_it.x = (center_mmap(r->minim.xpmw, r->map.msize.j, block));
		map.i = (int)(pix.y / block);
		while (pix.x++ <= r->minim.xpmw)
		{
			map.j = pix.x / block;
			if (map.j <= r->map.msize.j && map.i <= r->map.msize.i && \
			r->map.map[map.i][map.j] == '1')
				ft_put_pixel(&r->minim, draw_it.x, draw_it.y, MMAP);
			draw_it.x++;
		}
		draw_it.y++;
	}
	return (true);
}
