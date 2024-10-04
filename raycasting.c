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

float	get_correct_distance(float horizontal, float vertical, t_data *data, int i)
{
	float	distance = 0;
	float	smallest;

	(void)data;
	float angle_rayon = (i - SCREEN_WIDTH / 2) * 0.0571;
	if (horizontal < vertical || vertical < 0)
		smallest = horizontal;
	else
		smallest = vertical;
	// if (data->angle < 90)
	distance = smallest * cosf(angle_rayon * (PI / 180.0f));
	// else if (data->angle > 90)
	// 	distance = smallest * cosf(-30 * (PI / 180.0f));
	return (distance);
}

float	get_vertical_intersection(t_data *data)
{
	float	Xa;
	float	Ya;
	float	Bx;
	float	By;
	float	PB;

	Xa = -64;
	Ya = -1 * (CUB * tanf(data->angle * (PI / 180.0f)));
	// printf("Ya : %f\n", Ya);
	Bx = (int)(data->Px / CUB) * CUB - 1;
	// printf("Bx : %f\n", Bx);
	By = (data->Py) - (fabs((data->Px) - Bx) * tanf(data->angle * (PI / 180.0f)));
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
		PB = fabs(data->Px * 64 - Bx) / cosf(data->angle * (PI / 180.0f));
	return (PB);
}

float	get_horizontal_intersection(t_data *data)
{
	float	Xa;
	float	Ya;
	float	Ax;
	float	Ay;
	float	PA;

	float angle_radians = data->angle * (PI / 180.0f);

	 if (fabsf(sinf(angle_radians)) < EPSILON)
        return -1;

	Ya = -64;
	Xa = -1 * (64 / tanf(data->angle * (PI / 180.0f)));
	// printf("Xa : %f\n", Xa);
	Ay = (int)(data->Py / 64) * 64 - 1;
	// printf("Ay : %f\n", Ay);
	Ax = data->Px - ((data->Py - Ay) / tanf(data->angle * (PI / 180.0f)));
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
		PA = fabs(data->Px - Ax) / cosf(data->angle * (PI / 180.0f));
	return (PA);
}

int	raycasting(t_data *data)
{
	int	i;
	float	horizontal = 0;
	float	vertical = 0;
	float	distance;

	i = 0;
	while (i < 33/*SCREEN_WIDTH*/)
	{
		horizontal = get_horizontal_intersection(data);
		printf("PA : %f\n", horizontal);
		vertical = -1/*get_vertical_intersection(data)*/;
		// printf("PB : %f\n", vertical);
		distance = get_correct_distance(horizontal, vertical, data, i);
		printf("i : %d : distance : %f\n", i, distance);
		draw_column(data, distance, i);
		i++;
		data->angle += (i * 0.0571);
		// printf("data->angle : %f\n", data->angle);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (0);
}
