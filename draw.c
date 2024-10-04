/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:08 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/03 20:13:11 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	ft_put_pixel(t_img *img, int colomn, int line, int color)
{
	*(int *)(img->addr + (line * img->length + colomn * (img->bpp / 8))) = color;
}
 
void	draw_column(t_data *data, int distance, int colomn)
{
	int	hp;
	int	i;
	int	hr;
	int	half_hp;

	i = 0;
	hr = CUB / 2;
	// printf("distance : %d\n", distance);
	// printf("distance : %f\n", DISTANCE);
	hp = CUB * DISTANCE / distance;
	// if (hp < 0)
	// 	hp *= -1;
	// printf("hp : %d\n", hp);
	half_hp = hp / 2;
	while (i < (hr - half_hp))
	{
		ft_put_pixel(&data->img, colomn, i, BLUE);
		i++;
	}
	while (i <= (hr + half_hp))
	{
		ft_put_pixel(&data->img, colomn, i, BROWN);
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		ft_put_pixel(&data->img, colomn, i, GREEN);
		i++;
	}
}