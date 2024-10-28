/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:08 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/25 15:03:25 by cdomet-d         ###   ########.fr       */
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
	t_draw		img;
	t_draw_co	tex;
	int			color;

	img.line = 0;
	img.p_height = r->d_screen / distance;
	img.hp_height = img.p_height * 0.5;
	img.wall_top = r->hs_height - img.hp_height;
	tex.col = (int)(r->i * r->cwall.xpmw) % r->cwall.xpmw;
	tex.line = (double)r->cwall.xpmh / img.p_height;
	tex.line_it = tex.line;
	if (img.wall_top < 0)
		tex.line = -img.wall_top * tex.line_it;
	while (img.line < img.wall_top && img.line < S_HEIGHT)
		ft_put_pixel(&r->img, col, img.line++, r->map.ceiling);
	while (img.p_height-- > 0 && img.line < S_HEIGHT)
	{
		if ((int)tex.line < r->cwall.xpmh && tex.col >= 0)
			color = *(int *)(r->cwall.sxpm + ((int)tex.line * r->cwall.len + \
			(int)tex.col * (r->cwall.bpp / 8)));
		ft_put_pixel(&r->img, col, img.line++, color);
		tex.line += tex.line_it;
	}
	while (img.line < S_HEIGHT)
		ft_put_pixel(&r->img, col, img.line++, r->map.floor);
}
