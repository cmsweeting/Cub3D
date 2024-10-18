/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:08 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/18 15:17:38 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_put_pixel(t_img *img, int colomn, int line, int color)
{
	char	*pixel;

	if (colomn < 0 || colomn >= S_WIDTH || line < 0 \
		|| line >= S_HEIGHT)
		return ;
	pixel = img->strxpm + (line * img->len + colomn * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_column(t_ray *rdata, double distance, int colomn)
{
	int	hp;
	int	i;
	int	j;
	int	half_hp;
	int	half_screen_height;

	i = 0;
	j = 0;
	hp = rdata->d_screen / distance;
	half_hp = hp * 0.5;
	half_screen_height = S_HEIGHT * 0.5;
	while (i < (half_screen_height - half_hp) && i < S_HEIGHT)
	{
		ft_put_pixel(&rdata->img, colomn, i, SKY);
		i++;
	}
	while (hp > 0 && i < S_HEIGHT)
	{
		rdata->color = *(int *)rdata->cwall.strxpm + (j * rdata->cwall.len + ((int)(rdata->i * 64) % 64) * (rdata->cwall.bpp / 8));
		ft_put_pixel(&rdata->img, colomn, i, rdata->color);
		i++;
		j++;
		hp--;
	}
	while (i < S_HEIGHT)
	{
		ft_put_pixel(&rdata->img, colomn, i, GROUND);
		i++;
	}
}
