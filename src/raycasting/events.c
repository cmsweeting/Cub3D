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

void	step_left(t_data *data, double x, double y)
{
	if (!check_collisions(data->p.x + y, data->p.y - x, data))
	{
		data->p.x += y;
		data->p.y -= x;
	}
}

void	step_right(t_data *data, double x, double y)
{
	if (!check_collisions(data->p.x - y, data->p.y + x, data))
	{
		data->p.x -= y;
		data->p.y += x;
	}
}

void	step_up(t_data *data, double x, double y)
{
	if (!check_collisions(data->p.x + x, data->p.x - y, data))
	{
		data->p.x += x;
		data->p.y -= y;
	}
}

void	step_down(t_data *data, double x, double y)
{
	if (!check_collisions(data->p.x - x, data->p.y + y, data))
	{
		data->p.x -= x;
		data->p.y += y;
	}
}

void	new_position(t_data *data, double angle)
{
	double	x;
	double	y;
	int		quarter;

	x = cosf(to_radian(data->p_angle)) * 0.1;
	y = sinf(to_radian(data->p_angle)) * 0.1;
	quarter = get_quarter(data, angle);
	if (quarter == 0 || quarter == 3)
		y *= -1;
}

void	move(int keysym, t_data *data)
{
	double	x;
	double	y;
	double	angle;

	angle = data->p_angle;
	// x = cosf(to_radian(data->p_angle)) * 0.1;
	// y = sinf(to_radian(data->p_angle)) * 0.1;
	if (keysym == XK_w || keysym == XK_s)
		new_position(data, angle);
		// step_up(data, x, y);
	// else if (keysym == XK_s)
	// 	step_down(data, x, y);
	else if (keysym == XK_a)
	{
		angle += 90;
		normalise_angle(&data->p_angle);
		new_position(data, angle);
		// step_left(data, x, y);
	}
	else if (keysym == XK_d)
	{
		angle -= 90;
		normalise_angle(&data->p_angle);
		new_position(data, angle);
		// step_right(data, x, y);
	}
	else if (keysym == XK_Left)
		data->p_angle += (20.0 * data->angle_bt_rays);
	else if (keysym == XK_Right)
		data->p_angle -= (20.0 * data->angle_bt_rays);
	normalise_angle(&data->p_angle);
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