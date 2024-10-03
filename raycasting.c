/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:02:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/03 19:59:55 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

double	get_correct_distance(double horizontal, double vertical, t_data *data)
{
	double	distance = 0;
	double	smallest;

	(void)data;
	if (horizontal < vertical || vertical < 0)
		smallest = horizontal;
	else
		smallest = vertical;
	// if (data->angle < 90)
	distance = smallest * cos(30 * (PI / 180));
	// else if (data->angle > 90)
	// 	distance = smallest * cos(-30 * (PI / 180));
	return (distance);
}

double	get_vertical_intersection(t_data *data)
{
	double	Xa;
	double	Ya;
	double	Bx;
	double	By;
	double	PB;

	Xa = -64;
	Ya = -1 * (CUB * tan(data->angle * (PI / 180)));
	// printf("Ya : %f\n", Ya);
	Bx = (int)(data->Px / CUB) * CUB - 1;
	// printf("Bx : %f\n", Bx);
	By = (data->Py) - (fabs((data->Px) - Bx) * tan(data->angle * (PI / 180)));
	// printf("By : %f\n", By);
	while (By >= 0 && By != -0 && By != -0 && Bx >= 0 && data->map[(int)(By / CUB)][(int)(Bx / CUB)] \
		&& data->map[(int)(By / CUB)][(int)(Bx / CUB)] != '1')
	{
		Bx += Xa;
		// printf("Bx : %f\n", Bx);
		By += Ya;
		// printf("By : %f\n", By);
	}
	// printf("Bx coordonnee : %f\n", (Bx / CUB));
	// printf("By coordonnee : %f\n", (By / CUB));
	// printf("map[By][Bx] : %c\n", data->map[(int)(By / CUB)][(int)(Bx / CUB)]);
	if (By < 0 || By == -0 || Bx < 0 || Bx == -0)
		PB = -1;
	else
		PB = fabs(data->Px * 64 - Bx) / cos(data->angle * (PI / 180));
	return (PB);
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
	// printf("Xa : %f\n", Xa);
	Ay = (int)(data->Py / 64) * 64 - 1;
	// printf("Ay : %f\n", Ay);
	Ax = data->Px - ((data->Py - Ay) / tan(data->angle * (PI / 180)));
	// printf("Ax : %f\n", Ax);
	while (data->map[(int)(Ay / CUB)][(int)(Ax / CUB)] && data->map[(int)(Ay / CUB)][(int)(Ax / CUB)] != '1')
	{
		Ax += Xa;
		Ay += Ya;
	}
	// printf("Ax : %f\n", Ax);
	// printf("Ax coordonnee : %f\n", (Ax / CUB));
	// printf("Ay : %f\n", Ay);
	// printf("Ay coordonnee : %f\n", (Ay / CUB));
	// printf("map[Ay][Ax] : %c\n", data->map[(int)(Ay / CUB)][(int)(Ax / CUB)]);
	if (data->map[(int)(Ay / CUB)][(int)(Ax / CUB)] != '1')
		PA = -1;
	else
		PA = fabs(data->Px - Ax) / cos(data->angle * (PI / 180));
	return (PA);
}

int	raycasting(t_data *data)
{
	int	i;
	double	horizontal = 0;
	double	vertical = 0;
	double	distance;

	i = 0;
	while (i < 31/*SCREEN_WIDTH*/)
	{
		horizontal = get_horizontal_intersection(data);
		// printf("PA : %f\n", horizontal);
		vertical = -1/*get_vertical_intersection(data)*/;
		// printf("PB : %f\n", vertical);
		distance = get_correct_distance(horizontal, vertical, data);
		printf("i : %d : distance : %f\n", i, distance);
		draw_column(data, distance, i);
		i++;
		data->angle += (i * 0.06);
		printf("data->angle : %f\n", data->angle);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (0);
}
