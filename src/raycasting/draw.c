/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:08 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/18 21:45:20 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_put_pixel(t_img *img, int col, int line, int color)
{
	char	*pixel;

	if (col < 0 || col >= S_WIDTH || line < 0 \
		|| line >= S_HEIGHT)
		return ;
	pixel = img->sxpm + (line * img->len + col * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_column(t_ray *r, double distance, int col)
{
	t_draw		dvl;
	t_draw_co	it;

	it.x = 0;
	dvl.v_it = 0;
	dvl.phght = r->d_screen / distance;
	it.x_it = (double)r->cwall.xpms / dvl.phght;
	dvl.h_phght = dvl.phght * 0.5;
	dvl.h_sheight = S_HEIGHT * 0.5;
	while (dvl.v_it < ((dvl.h_sheight) - dvl.h_phght) && dvl.v_it < S_HEIGHT)
		ft_put_pixel(&r->img, col, dvl.v_it++, SKY);
	it.y = (int)(r->i * r->cwall.xpms) % r->cwall.xpms;
	while (dvl.phght > 0 && dvl.v_it < S_HEIGHT)
	{
		r->color = *(int *)(r->cwall.sxpm + \
			((int)it.x * r->cwall.len + it.y * (r->cwall.bpp / 8)));
		ft_put_pixel(&r->img, col, dvl.v_it, r->color);
		dvl.v_it++;
		it.x += it.x_it;
		dvl.phght--;
	}
	while (dvl.v_it < S_HEIGHT)
		ft_put_pixel(&r->img, col, dvl.v_it++, GROUND);
}
