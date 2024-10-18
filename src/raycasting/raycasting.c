/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:29:50 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/18 16:41:00 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_collisions(double x, double y, t_ray *rdata)
{
	ssize_t	i;
	ssize_t	j;

	i = (ssize_t)y;
	j = (ssize_t)x;
	if (i < 0 || j < 0 || i > rdata->map.msize.i || j > rdata->map.msize.j \
		|| !rdata->map.map[i][j])
		return (-1);
	if (rdata->map.map[i][j] == '1')
		return (1);
	return (0);
}

int	find_wall(t_ray *rdata, t_point *pt, t_point *step)
{
	int	i;

	i = check_collisions(pt->x, pt->y, rdata);
	while (!i)
	{
		pt->x += step->x;
		pt->y += step->y;
		i = check_collisions(pt->x, pt->y, rdata);
	}
	return (i);
}

double	vertical_intersection(t_ray *rdata)
{
	t_point	step;

	step.x = 1;
	step.y = tan(radian(rdata->r_angle)) * 1;
	rdata->vhitpt.x = (int)(rdata->p.x);
	if (cos(radian(rdata->r_angle)) == 0)
		return (-1);
	if (rdata->r_angle > 90.0 && rdata->r_angle < 270.0)
	{
		step.x *= -1;
		rdata->vhitpt.x -= EP;
	}
	else
	{
		step.y *= -1;
		rdata->vhitpt.x += 1;
	}
	rdata->vhitpt.y = rdata->p.y + tan(radian(rdata->r_angle)) * (rdata->p.x - rdata->vhitpt.x);
	if (find_wall(rdata, &rdata->vhitpt, &step) == -1)
		return (-1);
	return (get_distance(&rdata->vhitpt, rdata));
}

double	horizontal_intersection(t_ray *rdata)
{
	t_point	step;

	step.y = 1;
	step.x = 0;
	if (cos(radian(rdata->r_angle)) != 0)
		step.x = 1 / tan(radian(rdata->r_angle));
	rdata->hhitpt.y = (int)(rdata->p.y);
	if (sin(radian(rdata->r_angle)) == 0)
		return (-1);
	if (rdata->r_angle > 0.0 && rdata->r_angle < 180.0)
	{
		step.y *= -1;
		rdata->hhitpt.y -= EP;
	}
	else
	{
		step.x *= -1;
		rdata->hhitpt.y += 1;
	}
	rdata->hhitpt.x = rdata->p.x;
	if (cos(radian(rdata->r_angle)) != 0)
		rdata->hhitpt.x = rdata->p.x + (rdata->p.y - rdata->hhitpt.y) / tan(radian(rdata->r_angle));
	if (find_wall(rdata, &rdata->hhitpt, &step) == -1)
		return (-1);
	return (get_distance(&rdata->hhitpt, rdata));
}

double	smallest_distance(double hor, double ver, t_ray *rdata)
{
	double	smallest;

	smallest = 0.0;
	if (ver == -1 || (hor < ver && hor > 0))
	{
		smallest = hor;
		rdata->i = rdata->hhitpt.x;
		if (rdata->r_angle > 0.0 && rdata->r_angle < 180.0)
			rdata->cwall = rdata->map.no;
		else
			rdata->cwall = rdata->map.so;
		return (smallest);
	}
	else if (ver > 0)
	{
		smallest = ver;
		rdata->i = rdata->vhitpt.y;
		if (rdata->r_angle > 90.0 && rdata->r_angle < 270.0)
			rdata->cwall = rdata->map.we;
		else
			rdata->cwall = rdata->map.ea;
	}
	printf(" i : %f\n", rdata->i);
	return (smallest);
}

void	fish_eye(double *distance, int i, t_ray *rdata)
{
	double	angle;

	angle = (i - S_WIDTH * 0.5) * rdata->rayspacing;
	*distance *= cos(radian(angle));
}

int	raycasting(t_ray *rdata)
{
	int		i;
	double	horizontal;
	double	vertical;
	double	distance;

	i = 0;
	move(rdata);
	rdata->r_angle = rdata->c_angle + 30.0f;
	normalise_angle(&rdata->r_angle);
	while (i < S_WIDTH)
	{
		horizontal = horizontal_intersection(rdata);
		vertical = vertical_intersection(rdata);
		distance = smallest_distance(horizontal, vertical, rdata);
		fish_eye(&distance, i, rdata);
		draw_column(rdata, distance, i);
		rdata->r_angle -= rdata->rayspacing;
		normalise_angle(&rdata->r_angle);
		i++;
	}
	mlx_put_image_to_window(rdata->mlx, rdata->win, \
		rdata->img.ptr, 0, 0);
	return (0);
}
