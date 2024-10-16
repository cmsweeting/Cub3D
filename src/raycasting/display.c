/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:29 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/16 15:56:07 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	get_angles(t_data *data, t_card pcard)
{
	if (pcard == EA)
		data->P_angle = 0.0;
	else if (pcard == NO)
		data->P_angle = 90.0;
	else if (pcard == WE)
		data->P_angle = 180.0;
	else if (pcard == SO)
		data->P_angle = 270.0;
	data->angle_bt_rays = 60.0 / (SCREEN_WIDTH -  1.0);
}

void	init_data(t_data *data, t_map *map)
{
	data->map = map->map;
	data->P.X = (double)map->p.j + 0.5;
	data->P.Y = (double)map->p.i + 0.5;
	data->map_x = map->msize.j - 1;
	data->map_y = map->msize.i - 1;
	data->distance_screen = (SCREEN_WIDTH * 0.5) / tanf(to_radian(FOV * 0.5));
	get_angles(data, map->pcard);
}

int	init_display(t_map *map, t_data *data)
{
	init_data(data, map);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	 	return (1);
	data->img.ptr = mlx_new_image(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->img.ptr)
		return (1);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp, &data->img.length, &data->img.endian);
	if (!data->img.addr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.ptr);
		return (1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (1);
	}
	return (0);
}

void	run_game(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &raycasting, data);
	mlx_hook(data->win_ptr, 2, 1L<<0, &keys, data);
	mlx_hook(data->win_ptr, 17, 0, &close_win, data);
	mlx_loop(data->mlx_ptr);
	clean_display(data);
}