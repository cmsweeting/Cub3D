/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:23:41 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/15 17:49:16 by csweetin         ###   ########.fr       */
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

double	to_radian(double angle)
{
	return (angle * (PI / 180.0f));
}

double	get_opposite(double adj, double angle)
{
	double	op;
	
	op = tanf(to_radian(angle)) * adj;
	return (op);
}

double	get_adjacent(double opposite, double angle)
{
	double	adj;
	
	adj = opposite / tanf(to_radian(angle));
	return (adj);
}

// int	get_quarter(t_data *data)
// {
// 	int	quarter;

// 	quarter = ((int)data->P_angle / 90) % 4;
// 	return (quarter);
// }

double	get_distance(t_point *pt, t_data *data)
{
	double	distance;

	distance = sqrtf(powf((data->P.X - pt->X), 2) + powf((data->P.Y - pt->Y), 2));
	return (distance);
}

void	normalise_angle(double *angle)
{
	if (*angle > 360)
		*angle -= 360;
	else if (*angle < 0)
		*angle += 360;
}
