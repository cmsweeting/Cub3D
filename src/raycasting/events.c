/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:10 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/18 14:59:23 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	new_position(t_ray *rdata, double angle)
{
	double	x;
	double	y;

	x = cos(radian(angle)) * 0.005;
	y = sin(radian(angle)) * 0.005;
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

void	move(t_ray *rdata)
{
	double	angle;

	if (rdata->moves.lturn)
		rdata->c_angle += (3.0 * rdata->rayspacing);
	if (rdata->moves.rturn)
		rdata->c_angle -= (3.0 * rdata->rayspacing);
	angle = rdata->c_angle;
	if (rdata->moves.down)
		angle += 180;
	if (rdata->moves.left)
	{
		if (rdata->moves.down)
			angle -= 45;
		else if (rdata->moves.up)
			angle += 45;
		else
			angle += 90;
	}
	if (rdata->moves.right)
	{
		if (rdata->moves.down)
			angle += 45;
		else if (rdata->moves.up)
			angle -= 45;
		else
			angle -= 90;
	}
	normalise_angle(&rdata->c_angle);
	if ((rdata->moves.down && rdata->moves.up) || (rdata->moves.right && rdata->moves.left))
		return ;
	else if (rdata->moves.down || rdata->moves.up || rdata->moves.right || rdata->moves.left)
		new_position(rdata, angle);
}

int	close_win(t_ray *rdata)
{
	mlx_loop_end(rdata->mlx);
	return (0);
}

int	key_press(int keysym, t_ray *rdata)
{
	if (keysym == XK_Escape)
		close_win(rdata);
	else
	{
		if (keysym == XK_w)
			rdata->moves.up = true;
		if (keysym == XK_s)
			rdata->moves.down = true;
		if (keysym == XK_a)
			rdata->moves.left = true;
		if (keysym == XK_d)
			rdata->moves.right = true;
		if (keysym == XK_Left)
			rdata->moves.lturn = true;
		if (keysym == XK_Right)
			rdata->moves.rturn = true;
	}
	return (0);
}

int	key_release(int keysym, t_ray *rdata)
{
	if (keysym == XK_w)
		rdata->moves.up = false;
	if (keysym == XK_s)
		rdata->moves.down = false;
	if (keysym == XK_a)
		rdata->moves.left = false;
	if (keysym == XK_d)
		rdata->moves.right = false;
	if (keysym == XK_Left)
		rdata->moves.lturn = false;
	if (keysym == XK_Right)
		rdata->moves.rturn = false;
	return (0);
}