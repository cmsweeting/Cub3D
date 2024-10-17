/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:23:41 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/17 15:08:59 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

double	to_radian(double angle)
{
	return (angle * (PI / 180.0f));
}

double	get_opposite(double adj, double angle)
{
	double	op;

	op = tanf(to_radian(angle)) * adj;
	return (op);
}

double	get_adjacent(double opposite, double angle)
{
	double	adj;

	adj = opposite / tanf(to_radian(angle));
	return (adj);
}

double	get_distance(t_point *pt, t_ray *rdata)
{
	double	d;

	d = sqrtf(powf((rdata->p.x - pt->x), 2) + powf((rdata->p.y - pt->y), 2));
	return (d);
}

void	normalise_angle(double *angle)
{
	if (*angle > 360)
		*angle -= 360;
	else if (*angle < 0)
		*angle += 360;
}
