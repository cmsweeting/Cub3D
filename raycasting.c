/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:29:50 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/15 15:31:52 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	check_collisions(double x, double y, char **map)
{
	int	i;
	int	j;

	i = (int)y;
	j = (int)x;
	if (i < 0 || j < 0 || i > 7 || j > 7 || !map[i][j])
		return (-1);
	if (map[i][j] == '1')
		return (1);
	return (0);
}

int	find_wall(t_data *data, t_point *pt, double stepX, double stepY)
{
	int		i;

	i = check_collisions(pt->distX, pt->distY, data->map);
	while (!i)
	{
		pt->distX += stepX;
		pt->distY += stepY;
		i = check_collisions(pt->distX, pt->distY, data->map);
	}
	return (i);
}

double	vertical_intersection(t_data *data)
{
	t_point pt;
	double	stepX;
	double	stepY;
	double	e;

	//get Bx and Xa
	stepX = CUB;
	pt.distX = (int)(data->Px);
	if (data->dir_ray > 90.0 && data->dir_ray < 270.0)
	{
		stepX *= -1;
		pt.distX -= EPSILON;
	}
	else
		pt.distX += CUB;
	//get By et Ya
	stepY = get_opposite(CUB, data->dir_ray);
	e = get_opposite(((data->Px) - pt.distX), data->dir_ray);
	pt.distY = data->Py + e;
	if (find_wall(data, &pt, stepX, stepY) == -1)
		return (-1);
	return (get_distance(&pt, data));
}

double	horizontal_intersection(t_data *data)
{
	t_point pt;
	double	stepX;
	double	stepY;
	double	e;

	//get Ay and Ya
	stepY = CUB;
	pt.distY = (int)(data->Py);
	if (data->dir_ray > 0.0 && data->dir_ray < 180.0)
	{
		stepY *= -1;
		pt.distY -= EPSILON;
	}
	else
		pt.distY += CUB;
	//get Ax and Xa
	stepX = get_adjacent(CUB, data->dir_ray);
	e = get_adjacent((data->Py - pt.distY), data->dir_ray);
	pt.distX = data->Px + e;
	if (find_wall(data, &pt, stepX, stepY) == -1)
		return (-1);
	return (get_distance(&pt, data));
}

double	smallest_distance(double hor, double ver, t_data *data)
{
	double	smallest;

	smallest = 0.0;
	if (ver == -1 || (hor < ver && hor > 0))
	{
		smallest = hor;
		// if (data->dir_ray > 0.0 && data->dir_ray < 180.0)
		data->color = WALL_N;
		// else
		// 	data->color = WALL_S;
		return (smallest);
	}
	else if (ver > 0)
	{
		smallest = ver;
		data->color = WALL_S;
		// if (data->dir_ray > 90.0 && data->dir_ray < 270.0)
		// 	data->color = WALL_W;
		// else
		// 	data->color = WALL_E;
	}
	return (smallest);
}

void	fish_eye(double *distance, int i, t_data *data)
{
	double	angle;

	angle = ((i - SCREEN_WIDTH / 2) * data->angle_bt_rays) * -1.0;
	*distance *= cosf(to_radian(angle));
}

int	raycasting(t_data *data)
{
	int	i;
	double	horizontal;
	double	vertical;
	double	distance;

	i = 0;
	data->dir_ray = data->P_angle + 30.0f;
	normalise_angle(&data->dir_ray);
	while (i < SCREEN_WIDTH)
	{
		horizontal = horizontal_intersection(data);
		vertical = vertical_intersection(data);
		if (i == SCREEN_WIDTH - 1)
		{
			printf("horizontal = %f\nvertical = %f\n", horizontal ,vertical);
		}
		distance = smallest_distance(horizontal, vertical, data);
		fish_eye(&distance, i, data);
		draw_column(data, distance, i);
		data->dir_ray -= data->angle_bt_rays;
		normalise_angle(&data->dir_ray);
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (0);
}
