/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:10 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/21 17:03:24 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	new_position(t_ray *r, double angle)
{
	double	x;
	double	y;

	x = cos(radian(angle)) * 0.1;
	y = sin(radian(angle)) * 0.1;
	y *= -1.0;
	x += r->p.x;
	y += r->p.y;
	if (((ssize_t)x >= 0 || (ssize_t)x <= r->map.msize.j) \
		&& r->map.map[(ssize_t)y][(ssize_t)x] != '1')
		r->p.x = x;
	if (((ssize_t)y >= 0 || (ssize_t)y <= r->map.msize.i) \
		&& r->map.map[(ssize_t)y][(ssize_t)x] != '1')
		r->p.y = y;
}

void	move(t_ray *r)
{
	double	angle;

	if (r->moves.lturn)
		r->c_angle += (10.0 * r->rayspacing);
	if (r->moves.rturn)
		r->c_angle -= (10.0 * r->rayspacing);
	normalise_angle(&r->c_angle);
	angle = r->c_angle;
	if (r->moves.down)
		angle += 180;
	if (r->moves.left)
	{
		if (r->moves.down)
			angle -= 45;
		else if (r->moves.up)
			angle += 45;
		else
			angle += 90;
	}
	if (r->moves.right)
	{
		if (r->moves.down)
			angle += 45;
		else if (r->moves.up)
			angle -= 45;
		else
			angle -= 90;
	}
	normalise_angle(&angle);
	if ((r->moves.down && r->moves.up) || (r->moves.right && r->moves.left))
		return ;
	else if (r->moves.down || r->moves.up || r->moves.right || r->moves.left)
		new_position(r, angle);
}

int	close_win(t_ray *r)
{
	mlx_loop_end(r->mlx);
	return (0);
}

int	key_press(int keysym, t_ray *r)
{
	if (keysym == XK_Escape)
		close_win(r);
	else
	{
		if (keysym == XK_w)
			r->moves.up = true;
		if (keysym == XK_s)
			r->moves.down = true;
		if (keysym == XK_a)
			r->moves.left = true;
		if (keysym == XK_d)
			r->moves.right = true;
		if (keysym == XK_Left)
			r->moves.lturn = true;
		if (keysym == XK_Right)
			r->moves.rturn = true;
	}
	return (0);
}

int	key_release(int keysym, t_ray *r)
{
	if (keysym == XK_w)
		r->moves.up = false;
	if (keysym == XK_s)
		r->moves.down = false;
	if (keysym == XK_a)
		r->moves.left = false;
	if (keysym == XK_d)
		r->moves.right = false;
	if (keysym == XK_Left)
		r->moves.lturn = false;
	if (keysym == XK_Right)
		r->moves.rturn = false;
	return (0);
}
