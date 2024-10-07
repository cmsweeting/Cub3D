/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:10 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/07 15:58:46 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	move(int keysym, t_data *data)
{
	if (keysym == XK_w)
	{
		data->left = true;
		data->Py -= 1;
		data->ray_angle = 60;
	}
	else if (keysym == XK_s)
	{
		data->left = true;
		data->Py += 1;
		data->ray_angle = 60;
	}
	else if (keysym == XK_a)
	{
		data->left = true;
		data->P_angle += 1;
		data->Px -= 1;
		data->ray_angle = 60;
	}
	else if (keysym == XK_d)
	{
		data->left = true;
		data->P_angle += 1;
		data->Px += 1;
		data->ray_angle = 60;
	}
}

int	close_win(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	escape(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_win(data);
	move(keysym, data);
	return (0);
}
