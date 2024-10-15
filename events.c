/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:10 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/14 18:22:03 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	step_left(t_data *data, double x, double y)
{
	if (!check_collisions(data->Px + y, data->Py - x, data->map))
	{
		data->Px += y;
		data->Py -= x;
	}
}
void	step_right(t_data *data, double x, double y)
{
	if (!check_collisions(data->Px - y, data->Py + x, data->map))
	{
		data->Px -= y;
		data->Py += x;
	}
}
void	step_up(t_data *data, double x, double y)
{
	if (!check_collisions(data->Px + x, data->Py - y, data->map))
	{
		data->Px += x;
		data->Py -= y;
	}
}
void	step_down(t_data *data, double x, double y)
{
	if (!check_collisions(data->Px - x, data->Py + y, data->map))
	{
		data->Px -= x;
		data->Py += y;
	}
}

void	move(int keysym, t_data *data)
{
	double	x;
	double	y;

	x = cosf(to_radian(data->P_angle)) * 0.1;
	y = sinf(to_radian(data->P_angle)) * 0.1;
	if (keysym == XK_w)
		step_up(data, x, y);
	else if (keysym == XK_s)
		step_down(data, x, y);
	else if (keysym == XK_a)
		step_left(data, x, y);
	else if (keysym == XK_d)
		step_right(data, x, y);
	else if (keysym == XK_Left)
		data->P_angle += (20.0 * data->angle_bt_rays);
	else if (keysym == XK_Right)
		data->P_angle -= (20.0 * data->angle_bt_rays);
	normalise_angle(&data->P_angle);
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
