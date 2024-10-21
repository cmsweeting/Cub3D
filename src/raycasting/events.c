/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:10 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/18 21:46:06 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
