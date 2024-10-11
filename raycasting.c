/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:02:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/11 15:59:37 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

float	get_correct_distance(float horizontal, float vertical, t_data *data)
{
	float	distance;
	float	smallest;
	float 	angle;

	(void)distance;
	distance = 0;
	angle = 90.0f - data->ray_angle;
	if (!data->left)
		angle *= -1;
	if (horizontal < vertical || vertical < 0)
	{
		smallest = horizontal;
		data->color = WALL_N;
	}
	else
	{
		smallest = vertical;
		data->color = WALL_S;
	}
	distance = smallest * cosf(to_radian(angle));
	return (smallest);
}

int	check_collisions(float x, float y, char **map)
{
	int	i;
	int	j;

	i = (int)(y / CUB);
	j = (int)(x / CUB);
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

	Xa = CUB;
	Ya = CUB * tanf(to_radian(data->ray_angle));
	if (data->dir_ray > 0.0f && data->dir_ray < 180.0f)
		Ya *= -1;
	Bx = (int)(data->Px / CUB) * CUB;
	if (data->dir_ray > 90.0f && data->dir_ray < 270.0f)
	{
		Xa *= -1;
		Bx -= EPSILON;//0.1f;*/1.0f;
	}
	else
		Bx += CUB;
	float	y = fabs((data->Px) - Bx) * tanf(to_radian(data->ray_angle));
	if (data->dir_ray > 0.0f && data->dir_ray < 180.0f)
		By = (data->Py) - y;
	else
		By = (data->Py) + y;
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
		PB = /*sqrtf(powf((data->Px - Bx), 2) + powf((data->Py - By), 2));/*/fabs(data->Px * CUB - Bx) / cosf(to_radian(data->ray_angle));
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

	Ya = CUB;
	Xa = CUB / tanf(to_radian(data->ray_angle));
	if (data->dir_ray > 90.0f && data->dir_ray < 270.0f)
		Xa *= -1;
	Ay = (int)(data->Py / CUB) * CUB;
	if (data->dir_ray > 0.0f && data->dir_ray < 180.0f)
	{
		Ya *= -1;
		Ay -= EPSILON;//0.1f;*/1.0f;
	}
	else
		Ay += CUB;
	float	x = fabs(data->Py - Ay) / tanf(to_radian(data->ray_angle));
	if (data->dir_ray > 90.0f && data->dir_ray < 270.0f)
		Ax = data->Px - x;
	else
		Ax = data->Px + x;
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
		PA = /*sqrtf(powf((data->Px - Ax), 2) + powf((data->Py - Ay), 2));/*/fabs(data->Px - Ax) / cosf(to_radian(data->ray_angle));
	return (PA);
}

void	change_side(t_data *data, float *j)
{
	data->left = false;
	data->angle_bt_rays *= -1;
	*j = 1.0f;
}

int	raycasting(t_data *data)
{
	int	i;
	float	horizontal;
	float	vertical;
	float	distance;
	float		j;

	i = 0;
	j = -1.0f;
	data->ray_angle = 60.0f;
	data->left = true;
	data->dir_ray = data->P_angle + 30.0f;
	if (data->dir_ray > 360.0f)
		data->dir_ray -= 360;
	// printf("dir ray : %f\n", data->dir_ray);
	while (i < SCREEN_WIDTH)
	{
		if (data->ray_angle >= 90.0f)
			if (data->left)
				change_side(data, &j);
		horizontal = get_horizontal_intersection(data);
		vertical = get_vertical_intersection(data);
		distance = get_correct_distance(horizontal, vertical, data);
		draw_column(data, distance, i);
		data->ray_angle += data->angle_bt_rays;
		data->dir_ray += data->angle_bt_rays * j;
		if (data->dir_ray < 0.0f)
			data->dir_ray = 360 - data->ray_angle;
		// printf("PA : %f\n", horizontal);
		// printf("PB : %f\n", vertical);
		// printf("i : %d : distance : %f\n", i, distance);
		// printf("i : %d | dir ray : %f | ray angle : %f\n", i, data->dir_ray, data->ray_angle);
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (0);
}

// float angle_radians = data->ray_angle * (PI / 180.0f);

	//  if (fabsf(sinf(angle_radians)) < EPSILON)
    //     return -1;
