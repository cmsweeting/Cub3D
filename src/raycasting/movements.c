/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:16:41 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/25 18:47:11 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	new_position(t_ray *r, double angle)
{
	double	x;
	double	y;
	double	x2;
	double	y2;

	x = cos(radian(angle)) * 0.05;
	y = sin(radian(angle)) * 0.05;
	y *= -1.0;
	x += r->p.x;
	y += r->p.y;
	x2 = cos(radian(angle)) * 0.1;
	y2 = sin(radian(angle)) * 0.1;
	y2 *= -1.0;
	x2 += r->p.x;
	y2 += r->p.y;
	if (((ssize_t)x2 >= 0 && (ssize_t)x2 <= r->map.msize.j) \
		&& r->map.map[(ssize_t)r->p.y][(ssize_t)x2] != '1')
		r->p.x = x;
	if (((ssize_t)y2 >= 0 && (ssize_t)y2 <= r->map.msize.i) \
		&& r->map.map[(ssize_t)y2][(ssize_t)r->p.x] != '1')
		r->p.y = y;
}

static void	move_angle(t_ray *r, double *angle)
{
	*angle = r->c_angle;
	if (r->moves.down)
		*angle += 180;
	if (r->moves.left)
	{
		if (r->moves.down)
			*angle -= 45;
		else if (r->moves.up)
			*angle += 45;
		else
			*angle += 90;
	}
	if (r->moves.right)
	{
		if (r->moves.down)
			*angle += 45;
		else if (r->moves.up)
			*angle -= 45;
		else
			*angle -= 90;
	}
	normalise_angle(angle);
}

void	move(t_ray *r)
{
	double	angle;

	if (r->moves.lturn)
		r->c_angle += 1.0;
	if (r->moves.rturn)
		r->c_angle -= 1.0;
	normalise_angle(&r->c_angle);
	move_angle(r, &angle);
	if ((r->moves.down && r->moves.up) || (r->moves.right && r->moves.left))
		return ;
	else if (r->moves.down || r->moves.up || r->moves.right || r->moves.left)
		new_position(r, angle);
}
