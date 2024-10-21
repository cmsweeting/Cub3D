/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:08 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/21 11:43:18 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_put_pixel(t_img *img, int col, int line, int color)
{
	char	*pixel;

	if (col < 0 || col >= S_WIDTH || line < 0 || line >= S_HEIGHT)
		return ;
	pixel = img->sxpm + (line * img->len + col * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_column(t_ray *r, double distance, int col)
{
	t_draw		d;
	t_draw_co	it;

	d.cur_col = 0;
	it.line = 0.0;
	d.p_height = r->d_screen / distance;
	it.line = (double)r->cwall.xpms / d.p_height;
	d.hp_height = d.p_height * 0.5;
	d.hs_height = S_HEIGHT * 0.5;
	it.line_it = (double)r->cwall.xpms / d.p_height;
	d.wall_top = d.hs_height - d.hp_height;
	if (d.wall_top < 0)
		it.line = -d.wall_top * it.line_it;
	while (d.cur_col < ((d.hs_height) - d.hp_height) && d.cur_col < S_HEIGHT)
		ft_put_pixel(&r->img, col, d.cur_col++, r->map.ceiling);
	it.col = (int)(r->i * r->cwall.xpms) % r->cwall.xpms;
	while (d.p_height-- > 0 && d.cur_col < S_HEIGHT)
	{
		r->color = *(int *)(r->cwall.sxpm + \
			((int)it.line * r->cwall.len + it.col * (r->cwall.bpp / 8)));
		ft_put_pixel(&r->img, col, d.cur_col++, r->color);
		it.line += it.line_it;
	}
	while (d.cur_col < S_HEIGHT)
		ft_put_pixel(&r->img, col, d.cur_col++, r->map.floor);
}
