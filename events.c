/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:10 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/07 18:47:42 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	move(int keysym, t_data *data)
{
	if (keysym == XK_w)
	{
		data->left = true;
		data->Py -= 10;
		data->ray_angle = 60;
	}
	else if (keysym == XK_s)
	{
		data->left = true;
		data->Py += 10;
		data->ray_angle = 60;
	}
	else if (keysym == XK_a)
	{
		data->left = true;
		data->P_angle += (10 * data->angle_bt_rays);
		data->Px -= 10;
		data->ray_angle = 60;
	}
	else if (keysym == XK_d)
	{
		data->left = true;
		data->P_angle += (10 * data->angle_bt_rays);
		data->Px += 10;
		data->ray_angle = 60;
	}
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
