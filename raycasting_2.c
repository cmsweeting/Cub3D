/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:29:50 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/14 17:02:45 by csweetin         ###   ########.fr       */
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

double	get_vertical_intersection(t_data *data, t_point *pt)
{
	double	stepX;
	double	stepY;
	double	e;

	//get Bx and Xa
	stepX = CUB;
	pt->distX = (int)(data->Px);
	if (data->dir_ray > 90.0f && data->dir_ray < 270.0f)
	{
		stepX *= -1;
		pt->distX -= EPSILON;
	}
	else
		pt->distX += CUB;
	
	//get By et Ya
	if ((data->dir_ray > 0.0f && data->dir_ray < 90.0f) 
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
	if (find_wall(data, pt, stepX, stepY) == -1)
		return (-1);
	return (get_distance(pt, data));
}

double	get_horizontal_intersection(t_data *data, t_point *pt)
{
	double	stepX;
	double	stepY;
	double	e;

	//get Ay and Ya
	stepY = CUB;
	pt->distY = (int)(data->Py);
	if (data->dir_ray > 0.0f && data->dir_ray < 180.0f)
	{
		stepY *= -1;
		pt->distY -= EPSILON;
	}
	else
		pt->distY += CUB;
	
	//get Ax and Xa
	if ((data->dir_ray > 0.0f && data->dir_ray < 90.0f)
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
	if (find_wall(data, pt, stepX, stepY) == -1)
		return (-1);
	return (get_distance(pt, data));
}

double	get_smallest_distance(double hor, double ver, t_data *data)
{
	double	smallest;

	if (ver == -1 || (hor < ver && hor > 0))
	{
		smallest = hor;
		if (data->dir_ray > 0.0f && data->dir_ray < 180.0f)
			data->color = WALL_N;
		else
			data->color = WALL_S;
		return (smallest);
	}
	else if (ver > 0)
	{
		smallest = ver;
		if (data->dir_ray > 90.0f && data->dir_ray < 270.0f)
			data->color = WALL_W;
		else
			data->color = WALL_E;
	}
	return (smallest);
}

void	fish_eye(double *distance, int i, t_data *data)
{
	double	angle;

	(void)i;
	angle = ((i - SCREEN_WIDTH / 2) * data->angle_bt_rays) *  -1.0f;
	*distance *= cosf(to_radian(angle));
}

int	raycasting(t_data *data)
{
	int	i;
	t_point	horizontal;
	t_point	vertical;
	double	h;
	double	v;
	double	distance;

	i = 0;
	data->dir_ray = data->P_angle + 30.0f;
	if (data->dir_ray > 360.0f)
		data->dir_ray -= 360;
	leftmost_angle(data);
	data->ray_angle += 30.0f;
	while (i < SCREEN_WIDTH)
	{
		if (data->ray_angle <= 0.0f)
			data->ray_angle = 90.0f;
		h = get_horizontal_intersection(data, &horizontal);
		v = get_vertical_intersection(data, &vertical);
		distance = get_smallest_distance(h, v, data);
		fish_eye(&distance, i, data);
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
