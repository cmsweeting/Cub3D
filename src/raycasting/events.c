/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:10 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/17 19:25:48 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	new_position(t_ray *rdata, double angle)
{
	double	x;
	double	y;

	x = cosf(to_radian(angle)) * 0.2;
	y = sinf(to_radian(angle)) * 0.2;
	y *= -1.0;
	x += rdata->p.x;
	y += rdata->p.y;
	if (((ssize_t)x >= 0 || (ssize_t)x <= rdata->map.msize.j) \
		&& rdata->map.map[(ssize_t)y][(ssize_t)x] != '1')
		rdata->p.x = x;
	if (((ssize_t)y >= 0 || (ssize_t)y <= rdata->map.msize.i) \
		&& rdata->map.map[(ssize_t)y][(ssize_t)x] != '1')
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
	mlx_loop_end(rdata->mlx);
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
