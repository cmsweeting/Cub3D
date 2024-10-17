/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:10 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/17 14:59:14 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	new_position(t_ray *rdata, double angle)
{
	double	x;
	double	y;

	x = cosf(to_radian(angle)) * 0.2;
	y = sinf(to_radian(angle)) * 0.2;
	y *= -1.0;
	x += rdata->p.x;
	y += rdata->p.y;
	if ((int)x >= 0 || (int)x <= rdata->maplen.j)
		rdata->p.x = x;
	if ((int)y >= 0 || (int)y <= rdata->maplen.i)
		rdata->p.y = y;
}

void	move(int keysym, t_ray *rdata)
{
	double	angle;

	angle = rdata->c_angle;
	if (keysym == XK_w)
		new_position(rdata, angle);
	else if (keysym == XK_s)
	{
		angle += 180;
		normalise_angle(&rdata->c_angle);
		new_position(rdata, angle);
	}
	else if (keysym == XK_a)
	{
		angle += 90;
		normalise_angle(&rdata->c_angle);
		new_position(rdata, angle);
	}
	else if (keysym == XK_d)
	{
		angle -= 90;
		normalise_angle(&rdata->c_angle);
		new_position(rdata, angle);
	}
	else if (keysym == XK_Left)
		rdata->c_angle += (30.0 * rdata->rayspacing);
	else if (keysym == XK_Right)
		rdata->c_angle -= (30.0 * rdata->rayspacing);
}

int	close_win(t_ray *rdata)
{
	mlx_loop_end(rdata->mlx.mlx);
	return (0);
}

int	keys(int keysym, t_ray *rdata)
{
	if (keysym == XK_Escape)
		close_win(rdata);
	else
		move(keysym, rdata);
	return (0);
}
