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

void	step_left(t_data *data, float adj, float op, int quarter)
{
	float	x;
	float	y;
	
	x = adj;
	y = op;
	if (quarter == 0 || quarter == 2)
	{
		x = op;
		y = adj;
	}
	if (quarter == 0 || quarter == 1)
		x *= -1;
	if (quarter == 0 || quarter == 3)
		y *= -1;
	data->Px += x;
	data->Py += y;
}
void	step_right(t_data *data, float adj, float op, int quarter)
{
	float	x;
	float	y;
	
	x = adj;
	y = op;
	if (quarter == 0 || quarter == 2)
	{
		x = op;
		y = adj;
	}
	if (quarter == 2 || quarter == 3)
		x *= -1;
	if (quarter == 1 || quarter == 2)
		y *= -1;
	data->Px += x;
	data->Py += y;
}
void	step_up(t_data *data, float adj, float op, int quarter)
{
	float	x;
	float	y;
	
	x = adj;
	y = op;
	if (quarter == 1 || quarter == 3)
	{
		x = op;
		y = adj;
	}
	if (quarter == 1 || quarter == 2)
		x *= -1;
	if (quarter == 0 || quarter == 1)
		y *= -1;
	data->Px += x;
	data->Py += y;
}
void	step_down(t_data *data, float adj, float op, int quarter)
{
	float	x;
	float	y;
	
	x = adj;
	y = op;
	if (quarter == 1 || quarter == 3)
	{
		x = op;
		y = adj;
	}
	if (quarter == 0 || quarter == 3)
		x *= -1;
	if (quarter == 2 || quarter == 3)
		y *= -1;
	data->Px += x;
	data->Py += y;
}

void	move(int keysym, t_data *data)
{
	// if (keysym == XK_l)
	// 	raycasting(data);
	int		quarter;
	float	angle;
	float	adj;
	float	op;
	

	quarter = get_quarter(data);
	angle = data->P_angle - (90 * (quarter + 1));
	adj = cos(angle) * 0.1f;
	op = sin(angle) * 0.1f;
	if (keysym == XK_w)
		step_up(data, adj, op, quarter);
	else if (keysym == XK_s)
		step_down(data, adj, op, quarter);
	else if (keysym == XK_a)
		step_left(data, adj, op, quarter);
	else if (keysym == XK_d)
		step_right(data, adj, op, quarter);
	else if (keysym == XK_Left)
		data->P_angle += (10.0f * data->angle_bt_rays);
	else if (keysym == XK_Right)
		data->P_angle -= (10.0f * data->angle_bt_rays);
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
