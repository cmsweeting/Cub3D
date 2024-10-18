/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:08 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/18 17:46:32 by cdomet-d         ###   ########.fr       */
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
	int	line;
	int	half_hp;
	int	half_screen_height;
	int col;
	

	printf("strlen : %ld\n", strlen(rdata->cwall.strxpm));
	i = 0;
	line = 0;
	hp = rdata->d_screen / distance;
	half_hp = hp * 0.5;
	half_screen_height = S_HEIGHT * 0.5;
	while (i < (half_screen_height - half_hp) && i < S_HEIGHT)
		ft_put_pixel(&rdata->img, colomn, i++, SKY);
	col = (int)((rdata->i) * 64.0) % 64;
	// if (colomn == 0)
	// 	printf("col : %d\n", (int)(rdata->i * 64) % 64);
	while (hp > 0 && i < S_HEIGHT)
	{
		
		rdata->color = *(int *)rdata->cwall.strxpm + ((line * rdata->cwall.len + col) * (rdata->cwall.bpp / 8));
		// printf("index: %d\n", ((line * rdata->cwall.len + col) * (rdata->cwall.bpp / 8)) / 64);
		ft_put_pixel(&rdata->img, colomn, i, rdata->color);
		i++;
		line++;
		hp--;
	}
	while (i < S_HEIGHT)
	{
		ft_put_pixel(&rdata->img, colomn, i, GROUND);
		i++;
	}
}
