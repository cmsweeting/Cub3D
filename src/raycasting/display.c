/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:29 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/16 18:31:35 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	get_angles(t_data *data, t_card pcard)
{
	if (pcard == EA)
		data->p_angle = 0.0;
	else if (pcard == NO)
		data->p_angle = 90.0;
	else if (pcard == WE)
		data->p_angle = 180.0;
	else if (pcard == SO)
		data->p_angle = 270.0;
	data->angle_bt_rays = 60.0 / (S_WIDTH - 1.0);
}

void	init_data(t_data *data, t_map *map)
{
	data->map = map->map;
	data->p.x = (double)map->p.j + 0.5;
	data->p.y = (double)map->p.i + 0.5;
	data->map_x = map->msize.j - 1;
	data->map_y = map->msize.i - 1;
	data->distance_screen = (S_WIDTH * 0.5) / tanf(to_radian(FOV * 0.5));
	get_angles(data, map->pcard);
}

int	init_display(t_map *map, t_data *data)
{
	init_data(data, map);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->img.ptr = mlx_new_image(data->mlx_ptr, S_WIDTH, S_HEIGHT);
	if (!data->img.ptr)
		return (1);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp, \
					&data->img.length, &data->img.endian);
	if (!data->img.addr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.ptr);
		return (1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, S_WIDTH, S_HEIGHT, "Cub3D");
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
	mlx_hook(data->win_ptr, 2, 1L << 0, &keys, data);
	mlx_hook(data->win_ptr, 17, 0, &close_win, data);
	mlx_loop(data->mlx_ptr);
	clean_display(data);
}
