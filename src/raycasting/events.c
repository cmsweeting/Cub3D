/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:10 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/16 19:01:28 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	new_position(t_data *data, double angle)
{
	double	x;
	double	y;

	x = cosf(to_radian(angle)) * 0.2;
	y = sinf(to_radian(angle)) * 0.2;
	y *= -1.0;
	x += data->p.x;
	y += data->p.y;
	if ((int)x >= 0 || (int)x <= data->map_x)
		data->p.x = x;
	if ((int)y >= 0 || (int)y <= data->map_y)
		data->p.y = y;
}

void	move(int keysym, t_data *data)
{
	double	angle;

	angle = data->p_angle;
	if (keysym == XK_w)
		new_position(data, angle);
	else if (keysym == XK_s)
	{
		angle += 180;
		normalise_angle(&data->p_angle);
		new_position(data, angle);
	}
	else if (keysym == XK_a)
	{
		angle += 90;
		normalise_angle(&data->p_angle);
		new_position(data, angle);
	}
	else if (keysym == XK_d)
	{
		angle -= 90;
		normalise_angle(&data->p_angle);
		new_position(data, angle);
	}
	else if (keysym == XK_Left)
		data->p_angle += (30.0 * data->angle_bt_rays);
	else if (keysym == XK_Right)
		data->p_angle -= (30.0 * data->angle_bt_rays);
}

int	close_win(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	keys(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_win(data);
	else
		move(keysym, data);
	return (0);
}
