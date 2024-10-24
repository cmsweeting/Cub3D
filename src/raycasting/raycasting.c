/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:29:50 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/24 10:10:05 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	vertical_hitpt(t_ray *r)
{
	r->i = fmod(r->vhitpt.y, 1.0);
	if (r->r_angle > 90.0 && r->r_angle < 270.0)
	{
		r->i = 1.0 - r->i;
		r->cwall = r->map.we;
	}
	else
		r->cwall = r->map.ea;
}

static double	smallest_distance(double hor, double ver, t_ray *r)
{
	double	smallest;

	smallest = 1.0;
	if (ver == -1 || (hor < ver && hor > 0))
	{
		smallest = hor;
		r->i = fmod(r->hhitpt.x, 1.0);
		if (r->r_angle > 0.0 && r->r_angle < 180.0)
			r->cwall = r->map.no;
		else
		{
			r->i = 1.0 - r->i;
			r->cwall = r->map.so;
		}
		return (smallest);
	}
	else if (ver > 0)
	{
		smallest = ver;
		vertical_hitpt(r);
	}
	return (smallest);
}

static void	fish_eye(double *distance, int i, t_ray *r)
{
	double	angle;

	angle = (i - r->hs_width) * r->rayspacing;
	*distance *= cos(radian(angle));
}

int	raycasting(t_ray *r)
{
	int		i;
	double	horizontal;
	double	vertical;
	double	distance;

	i = 0;
	move(r);
	r->r_angle = r->c_angle + 30.0f;
	normalise_angle(&r->r_angle);
	while (i < S_WIDTH)
	{
		horizontal = horizontal_intersection(r);
		vertical = vertical_intersection(r);
		distance = smallest_distance(horizontal, vertical, r);
		fish_eye(&distance, i, r);
		draw_column(r, distance, i);
		r->r_angle -= r->rayspacing;
		normalise_angle(&r->r_angle);
		i++;
	}
	mlx_put_image_to_window(r->mlx, r->win, r->img.ptr, 0, 0);
	return (0);
}
