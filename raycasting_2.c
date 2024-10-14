/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:29:50 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/11 18:00:03 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

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

void	find_wall(t_data *data, t_point *pt, float stepX, float stepY)
{
	int		i;

	i = check_collisions(pt->distX, pt->distY, data->map);
	while (!i)
	{
		pt->distX += stepX;
		pt->distY += stepY;
		i = check_collisions(pt->distX, pt->distY, data->map);
	}
}

void	get_vertical_intersection(t_data *data, t_point *pt)
{
	float	stepX;
	float	stepY;
	float	e;

	//get Bx and Xa
	stepX = CUB;
	pt->distX = (int)(data->Px / CUB) * CUB;
	if (data->dir_ray > 90.0f && data->dir_ray < 270.0f)
	{
		stepX *= -1;
		pt->distX -= EPSILON;//0.1f;*/1.0f;
	}
	else
		pt->distX += CUB;
	
	//get By et Ya
	if ((data->dir_ray > 0.0f && data->dir_ray < 90.0f) \
		|| (data->dir_ray > 180.0f && data->dir_ray < 270.0f))
	{
		stepY = get_opposite(CUB, data->ray_angle);
		e = get_opposite(fabs((data->Px) - pt->distX), data->ray_angle);
	}
	else
	{
		stepY = get_adjacent(CUB, data->ray_angle);
		e = get_adjacent(fabs((data->Px) - pt->distX), data->ray_angle);
	}
	if (data->dir_ray > 0.0f && data->dir_ray < 180.0f)
	{
		stepY *= -1;
		e *= -1;;
	}
	pt->distY = data->Py + e;
	find_wall(data, pt, stepX, stepY);
}

void	get_horizontal_intersection(t_data *data, t_point *pt)
{
	float	stepX;
	float	stepY;
	float	e;

	//get Ay and Ya
	stepY = CUB;
	pt->distY = (int)(data->Py / CUB) * CUB;
	if (data->dir_ray > 0.0f && data->dir_ray < 180.0f)
	{
		stepY *= -1;
		pt->distY -= EPSILON;//0.1f;*/1.0f;
	}
	else
		pt->distY += CUB;
	
	//get Ax and Xa
	if ((data->dir_ray > 0.0f && data->dir_ray < 90.0f) \
		|| (data->dir_ray > 180.0f && data->dir_ray < 270.0f))
	{
		stepX = get_adjacent(CUB, data->ray_angle);
		e = get_adjacent(fabs(data->Py - pt->distY), data->ray_angle);
	}
	else
	{
		stepX = get_opposite(CUB, data->ray_angle);
		e = get_opposite(fabs(data->Py - pt->distY), data->ray_angle);
	}
	if (data->dir_ray > 90.0f && data->dir_ray < 270.0f)
	{
		stepX *= -1.0f;
		e *= -1.0f;
	}
	pt->distX = data->Px + e;
	find_wall(data, pt, stepX, stepY);
}

float	get_smallest_distance(t_point hor, t_point ver, t_data *data)
{
	float	smallest;
	float	dist_hor;
	float	dist_ver;
	int		hit_h;
	int		hit_v;
	
	hit_h = check_collisions(hor.distX, hor.distY, data->map);
	hit_v = check_collisions(ver.distX, ver.distY, data->map);
	if (hit_h == -1)
	{
		smallest = sqrtf(powf((data->Px - ver.distX), 2) + powf((data->Py - ver.distY), 2));
		data->color = WALL_S;
		return (smallest);
	}
	else if (hit_v == -1)
	{
		smallest = sqrtf(powf((data->Px - hor.distX), 2) + powf((data->Py - hor.distY), 2));
		data->color = WALL_N;
		return (smallest);
	}
	dist_hor = sqrtf(powf((data->Px - hor.distX), 2) + powf((data->Py - hor.distY), 2));
	dist_ver = sqrtf(powf((data->Px - ver.distX), 2) + powf((data->Py - ver.distY), 2));
	if (dist_hor < dist_ver)
	{
		smallest = dist_hor;
		data->color = WALL_N;
	}
	else
	{
		smallest = dist_ver;
		data->color = WALL_S;
	}
	return (smallest);
}

int	raycasting(t_data *data)
{
	int	i;
	t_point	horizontal;
	t_point	vertical;
	float	distance;

	i = 0;
	data->dir_ray = data->P_angle + 30.0f;
	if (data->dir_ray > 360.0f)
		data->dir_ray -= 360;
	// printf("dir angle : %f\n", data->dir_ray);
	// printf("ray angle : %f\n", data->ray_angle);
	while (i < SCREEN_WIDTH)
	{
		if (data->ray_angle <= 0.0f)
			data->ray_angle = 90.0f;
		// printf("ray angle : %f\n", data->ray_angle);
		// if (i == 526)
		// {
		// 	printf("dir angle : %f\n", data->dir_ray);
		// 	printf("ray angle : %f\n", data->ray_angle);
		// }
		get_horizontal_intersection(data, &horizontal);
		get_vertical_intersection(data, &vertical);
		distance = get_smallest_distance(horizontal, vertical, data);
		//fix_fish_eye
		draw_column(data, distance, i);
		data->ray_angle -= data->angle_bt_rays;
		data->dir_ray -= data->angle_bt_rays;
		if (data->dir_ray < 0.0f)
			data->dir_ray = 360 - data->ray_angle;
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (0);
}