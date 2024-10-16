/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:29:50 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/15 18:38:10 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	check_collisions(double x, double y, t_data *data)
{
	int	i;
	int	j;

	i = (int)y;
	j = (int)x;
	if (i < 0 || j < 0 || i > data->map_y || j > data->map_x || !data->map[i][j])
		return (-1);
	if (data->map[i][j] == '1')
		return (1);
	return (0);
}

int	find_wall(t_data *data, t_point *pt, t_point *step)
{
	int	i;

	i = check_collisions(pt->X, pt->Y, data);
	while (!i)
	{
		pt->X += step->X;
		pt->Y += step->Y;
		i = check_collisions(pt->X, pt->Y, data);
	}
	return (i);
}

double	vertical_intersection(t_data *data)
{
	t_point pt;
	t_point	step;

	step.X = 1;
	step.Y = get_opposite(1, data->ray_angle);
	pt.X = (int)(data->P.X);
	if (data->ray_angle > 90.0 && data->ray_angle < 270.0)
	{
		step.X *= -1;
		pt.X -= EPSILON;
	}
	else
		pt.X += 1;
	pt.Y = data->P.Y+ get_opposite((data->P.X) - pt.X, data->ray_angle);
	if (find_wall(data, &pt, &step) == -1)
		return (-1);
	return (get_distance(&pt, data));
}

double	horizontal_intersection(t_data *data)
{
	t_point pt;
	t_point	step;

	step.Y = 1;
	step.X = get_adjacent(1, data->ray_angle);
	pt.Y = (int)(data->P.Y);
	if (data->ray_angle > 0.0 && data->ray_angle < 180.0)
	{
		step.Y *= -1;
		pt.Y -= EPSILON;
	}
	else
		pt.Y += 1;
	pt.X = data->P.X + get_adjacent(data->P.Y- pt.Y, data->ray_angle);
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
		// if (data->ray_angle > 0.0 && data->ray_angle < 180.0)
		data->color = WALL_N;
		// else
		// 	data->color = WALL_S;
		return (smallest);
	}
	else if (ver > 0)
	{
		smallest = ver;
		data->color = WALL_S;
		// if (data->ray_angle > 90.0 && data->ray_angle < 270.0)
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
	data->ray_angle = data->P_angle + 30.0f;
	normalise_angle(&data->ray_angle);
	while (i < SCREEN_WIDTH)
	{
		horizontal = horizontal_intersection(data);
		vertical = vertical_intersection(data);
		// if (i == SCREEN_WIDTH - 1)
		// {
		// 	printf("horizontal = %f\nvertical = %f\n", horizontal ,vertical);
		// }
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
