/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:08 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/16 18:26:15 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	ft_put_pixel(t_img *img, int colomn, int line, int color)
{
	char	*pixel;

	if (colomn < 0 || colomn >= S_WIDTH || line < 0 \
		|| line >= S_HEIGHT)
		return ;
	pixel = img->addr + (line * img->length + colomn * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_column(t_data *data, double distance, int colomn)
{
	int	hp;
	int	i;
	int	half_hp;
	int	half_screen_height;

	i = 0;
	hp = data->distance_screen / distance;
	half_hp = hp * 0.5;
	half_screen_height = S_HEIGHT * 0.5;
	while (i < (half_screen_height - half_hp) && i < S_HEIGHT)
	{
		ft_put_pixel(&data->img, colomn, i, SKY);
		i++;
	}
	while (hp > 0 && i < S_HEIGHT)
	{
		ft_put_pixel(&data->img, colomn, i, data->color);
		i++;
		hp--;
	}
	while (i < S_HEIGHT)
	{
		ft_put_pixel(&data->img, colomn, i, GROUND);
		i++;
	}
}
