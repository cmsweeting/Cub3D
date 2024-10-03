/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:02:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/03 15:33:14 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

double	get_correct_distance(double horizontal, double vertical, t_data *data)
{
	double	distance = 0;
	double	smallest;

	(void)vertical;
	(void)data;
	// if (horizontal < vertical)
	smallest = horizontal;
	// else
	// 	smallest = vertical;
	// if (data->angle < 90)
	distance = smallest * cos(30 * (PI / 180));
	// else if (data->angle > 90)
	// 	distance = smallest * cos(-30 * (PI / 180));
	return (distance);
}

double	get_horizontal_intersection(t_data *data)
{
	double	Xa;
	double	Ya;
	double	Ax;
	double	Ay;
	double	PA;

	Ya = -64;
	Xa = -1 * (64 / tan(data->angle * (PI / 180)));
	// printf("Xa : %d\n", Xa);
	Ay = (int)(data->Py / 64) * 64 - 1;
	// printf("Ay : %d\n", Ay);
	Ax = data->Px - ((data->Py - Ay) / tan(data->angle * (PI / 180)));
	// printf("Ax : %d\n", Ax);
	while (data->map[(int)(Ay / CUB)][(int)(Ax / CUB)] && data->map[(int)(Ay / CUB)][(int)(Ax / CUB)] != '1')
	{
		Ax += Xa;
		Ay += Ya;
	}
	// printf("Ax : %d\n", Ax);
	// printf("Ax coordonnee : %d\n", (Ax / CUB));
	// printf("Ay : %d\n", Ay);
	// printf("Ay coordonnee : %d\n", (Ay / CUB));
	// printf("map[Ay][Ax] : %c\n", data->map[Ay / CUB][Ax / CUB]);
	PA = fabs(data->Px - Ax) / cos(data->angle * (PI / 180));
	return (PA);
}

int	raycasting(t_data *data)
{
	int	i;
	double	horizontal;
	int	vertical = 0;
	double	distance;

	i = 0;
	// while (i < 525/*SCREEN_WIDTH*/)
	// {
		horizontal = get_horizontal_intersection(data);
		// printf("PA : %f\n", horizontal);
		// vertical = get_vertical_intersection(data);
		distance = get_correct_distance(horizontal, vertical, data);
		// printf("distance : %f\n", distance);
		draw_column(data, distance, i);
		// i++;
		// data->angle += (i * data->angle_bt_rays);
	// }
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (0);
}
