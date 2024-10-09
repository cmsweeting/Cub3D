/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:08 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/09 18:20:23 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	ft_put_pixel(t_img *img, int colomn, int line, int color)
{
	if (colomn < 0 || colomn >= SCREEN_WIDTH || line < 0 || line >= SCREEN_HEIGHT)
		return ;
	*(int *)(img->addr + (line * img->length + colomn * (img->bpp / 8))) = color;
}
 
void	draw_column(t_data *data, float distance, int colomn)
{
	int	hp;
	int	i;
	int	half_hp;

	i = 0;
	distance *= 64;
	// printf("distance : %f\n", distance);
	hp = 64 * data->distance_screen / distance;
	// printf("hp : %d\n", hp);
	half_hp = hp / 2;
	int	half_screen_height = SCREEN_HEIGHT / 2;
	while (i < (half_screen_height - half_hp) && i < SCREEN_HEIGHT)
	{
		ft_put_pixel(&data->img, colomn, i, SKY);
		i++;
	}
	while (hp > 0 && i < SCREEN_HEIGHT)
	{
		ft_put_pixel(&data->img, colomn, i, data->color);
		i++;
		hp--;
	}
	while (i < SCREEN_HEIGHT)
	{
		ft_put_pixel(&data->img, colomn, i, GROUND);
		i++;
	}
}