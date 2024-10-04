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
	float	distance;
	float	smallest;
	float angle;
	
	(void)i;
	distance = 0;
	angle = 90 - data->ray_angle;//(i - SCREEN_WIDTH / 2) * 0.0571;
	if (horizontal < vertical || vertical < 0)
		smallest = horizontal;
	else
		smallest = vertical;
	distance = smallest * cosf(angle * (PI / 180.0f));
	return (distance);
}

int	check_collisions(float x, float y, char **map)
{
	int	i;
	int	j;

	i = y / 64;
	j = x / 64;
	if (i < 0 || j < 0 || i > 7 || j > 7 || !map[i][j])
		return (-1);
	if (map[i][j] == '1')
		return (1);
	return (0);
}

float	get_vertical_intersection(t_data *data)
{
	float	Xa;
	float	Ya;
	float	Bx;
	float	By;
	float	PB;
	int		i;

	Xa = -64;
	Ya = -1 * (CUB * tanf(data->ray_angle * (PI / 180.0f)));
	Bx = (int)(data->Px / CUB) * CUB - 1;
	By = (data->Py) - (fabs((data->Px) - Bx) * tanf(data->ray_angle * (PI / 180.0f)));
	i = check_collisions(Bx, By, data->map);
	while (!i)
	{
		Bx += Xa;
		By += Ya;
		i = check_collisions(Bx, By, data->map);
	}
	if (i == -1)
		PB = -1;
	else
		PB = fabs(data->Px * 64 - Bx) / cosf(data->ray_angle * (PI / 180.0f));
	return (PB);
}

float	get_horizontal_intersection(t_data *data)
{
	float	Xa;
	float	Ya;
	float	Ax;
	float	Ay;
	float	PA;
	int		i;

	Ya = -64;
	Xa = -1 * (64 / tanf(data->ray_angle * (PI / 180.0f)));
	Ay = (int)(data->Py / 64) * 64 - 1;
	Ax = data->Px - ((data->Py - Ay) / tanf(data->ray_angle * (PI / 180.0f)));
	i = check_collisions(Ax, Ay, data->map);
	while (!i)
	{
		Ax += Xa;
		Ay += Ya;
		i = check_collisions(Ax, Ay, data->map);
	}
	if (i == -1)
		PA = -1;
	else
		PA = fabs(data->Px - Ax) / cosf(data->ray_angle * (PI / 180.0f));
	return (PA);
}

int	raycasting(t_data *data)
{
	int	i;
	float	horizontal = 0;
	float	vertical = 0;
	float	distance;

	i = 0;
	while (i < 32/*SCREEN_WIDTH*/)
	{
		horizontal = get_horizontal_intersection(data);
		// printf("PA : %f\n", horizontal);
		vertical = get_vertical_intersection(data);
		// printf("PB : %f\n", vertical);
		distance = get_correct_distance(horizontal, vertical, data, i);
		// printf("i : %d : distance : %f\n", i, distance);
		draw_column(data, distance, i);
		i++;
		data->ray_angle += (i * data->angle_bt_rays);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (0);
}


// float angle_radians = data->ray_angle * (PI / 180.0f);

	//  if (fabsf(sinf(angle_radians)) < EPSILON)
    //     return -1;
