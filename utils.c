/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:23:41 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/14 18:17:14 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	clean_display(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

float	to_radian(float angle)
{
	return (angle * (PI / 180.0f));
}

float	get_opposite(float adj, float angle)
{
	float	op;
	
	op = tanf(to_radian(angle)) * adj;
	return (op);
}

float	get_adjacent(float opposite, float angle)
{
	float	adj;
	
	adj = opposite / tanf(to_radian(angle));
	return (adj);
}

int	get_quarter(t_data *data)
{
	int	quarter;

	quarter = ((int)data->P_angle / 90) % 4;
	return (quarter);
}

void	leftmost_angle(t_data *data)
{
	int		index_axis;
	float	angle_ref;
	
	index_axis = get_quarter(data);
	angle_ref = 90 * index_axis;
	data->ray_angle = data->P_angle - angle_ref;
	// printf("ray angle : %f\n", data->ray_angle);
}