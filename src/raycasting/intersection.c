/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:30:04 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/22 14:30:30 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	vertical_intersection(t_ray *r)
{
	t_point	step;

	step.x = 1;
	step.y = tan(radian(r->r_angle)) * 1;
	r->vhitpt.x = (int)(r->p.x);
	if (cos(radian(r->r_angle)) == 0)
		return (-1);
	if (r->r_angle > 90.0 && r->r_angle < 270.0)
	{
		step.x *= -1;
		r->vhitpt.x -= EP;
	}
	else
	{
		step.y *= -1;
		r->vhitpt.x += 1;
	}
	r->vhitpt.y = r->p.y + tan(radian(r->r_angle)) * (r->p.x - r->vhitpt.x);
	if (find_wall(r, &r->vhitpt, &step) == -1)
		return (-1);
	return (get_distance(&r->vhitpt, r));
}

double	horizontal_intersection(t_ray *r)
{
	t_point	step;

	step.y = 1;
	step.x = 0;
	if (cos(radian(r->r_angle)) != 0)
		step.x = 1 / tan(radian(r->r_angle));
	r->hhitpt.y = (int)(r->p.y);
	if (sin(radian(r->r_angle)) == 0)
		return (-1);
	if (r->r_angle > 0.0 && r->r_angle < 180.0)
	{
		step.y *= -1;
		r->hhitpt.y -= EP;
	}
	else
	{
		step.x *= -1;
		r->hhitpt.y += 1;
	}
	r->hhitpt.x = r->p.x;
	if (cos(radian(r->r_angle)) != 0)
		r->hhitpt.x = r->p.x + (r->p.y - r->hhitpt.y) / tan(radian(r->r_angle));
	if (find_wall(r, &r->hhitpt, &step) == -1)
		return (-1);
	return (get_distance(&r->hhitpt, r));
}
