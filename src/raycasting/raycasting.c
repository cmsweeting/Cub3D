/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:29:50 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/16 18:32:04 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	check_collisions(double x, double y, t_data *data)
{
	int	i;
	int	j;

	i = (int)y;
	j = (int)x;
	if (i < 0 || j < 0 || i > data->map_y || j > data->map_x \
		|| !data->map[i][j])
		return (-1);
	if (data->map[i][j] == '1')
		return (1);
	return (0);
}

int	find_wall(t_data *data, t_point *pt, t_point *step)
{
	int	i;

	i = check_collisions(pt->x, pt->y, data);
	while (!i)
	{
		pt->x += step->x;
		pt->y += step->y;
		i = check_collisions(pt->x, pt->y, data);
	}
	return (i);
}

double	vertical_intersection(t_data *data)
{
	t_point	pt;
	t_point	step;

	step.x = 1;
	step.y = get_opposite(1, data->ray_angle);
	pt.x = (int)(data->p.x);
	if (cos(to_radian(data->ray_angle)) == 0)
		return (-1);
	if (data->ray_angle > 90.0 && data->ray_angle < 270.0)
	{
		step.x *= -1;
		pt.x -= EPSILON;
	}
	else
	{
		step.y *= -1;
		pt.x += 1;
	}
	pt.y = data->p.y + get_opposite((data->p.x) - pt.x, data->ray_angle);
	if (find_wall(data, &pt, &step) == -1)
		return (-1);
	return (get_distance(&pt, data));
}

double	horizontal_intersection(t_data *data)
{
	t_point	pt;
	t_point	step;

	step.y = 1;
	step.x = 0;
	if (cos(to_radian(data->ray_angle)) != 0)
		step.x = get_adjacent(1, data->ray_angle);
	pt.y = (int)(data->p.y);
	if (sinf(to_radian(data->ray_angle)) == 0)
		return (-1);
	if (data->ray_angle > 0.0 && data->ray_angle < 180.0)
	{
		step.y *= -1;
		pt.y -= EPSILON;
	}
	else
	{
		step.x *= -1;
		pt.y += 1;
	}
	pt.x = data->p.x;
	if (cos(to_radian(data->ray_angle)) != 0)
		pt.x = data->p.x + get_adjacent(data->p.y - pt.y, data->ray_angle);
	if (find_wall(data, &pt, &step) == -1)
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
		if (data->ray_angle > 0.0 && data->ray_angle < 180.0)
			data->color = WALL_N;
		else
			data->color = WALL_S;
		return (smallest);
	}
	else if (ver > 0)
	{
		smallest = ver;
		if (data->ray_angle > 90.0 && data->ray_angle < 270.0)
			data->color = WALL_W;
		else
			data->color = WALL_E;
	}
	return (smallest);
}

void	fish_eye(double *distance, int i, t_data *data)
{
	double	angle;

	angle = (i - S_WIDTH * 0.5) * data->angle_bt_rays;
	*distance *= cosf(to_radian(angle));
}

int	raycasting(t_data *data)
{
	int		i;
	double	horizontal;
	double	vertical;
	double	distance;

	i = 0;
	data->ray_angle = data->p_angle + 30.0f;
	normalise_angle(&data->ray_angle);
	while (i < S_WIDTH)
	{
		horizontal = horizontal_intersection(data);
		vertical = vertical_intersection(data);
		distance = smallest_distance(horizontal, vertical, data);
		fish_eye(&distance, i, data);
		draw_column(data, distance, i);
		data->ray_angle -= data->angle_bt_rays;
		normalise_angle(&data->ray_angle);
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (0);
}
