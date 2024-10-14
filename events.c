/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:10 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/08 16:36:45 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	leftmost_angle(t_data *data)
{
	
}

void	move(int keysym, t_data *data)
{
	// if (keysym == XK_l)
	// 	raycasting(data);
	if (keysym == XK_w)
	{
		// data->Py -= sin(a) * 0.1
		// data->Px += cos(a) * 0.1;
		// OU
		// data->Px -= cos(a) * 0.1;
	}
	else if (keysym == XK_s)
	{
		// data->Py += sin(a) * 0.1;
		// data->Px += cos(a) * 0.1;
		// OU
		// data->Px -= cos(a) * 0.1;
	}
	else if (keysym == XK_a)
	{
		data->Px -= 0.1;
	}
	else if (keysym == XK_d)
	{
		data->Px += 0.1;
	}
	else if (keysym == XK_Left)
		data->P_angle -= (0.1 * data->angle_bt_rays);
	else if (keysym == XK_Right)
		data->P_angle += (0.1 * data->angle_bt_rays);
	leftmost_angle(data);
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
