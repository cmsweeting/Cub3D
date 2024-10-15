/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:29 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/14 18:24:17 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	get_angles(t_data *data)
{
	if (data->map[(int)data->Py][(int)data->Px] == 'E')
		data->P_angle = 0.0;
	else if (data->map[(int)data->Py][(int)data->Px] == 'N')
		data->P_angle = 90.0;
	else if (data->map[(int)data->Py][(int)data->Px] == 'W')
		data->P_angle = 180.0;
	else if (data->map[(int)data->Py][(int)data->Px] == 'S')
		data->P_angle = 270.0;
	data->angle_bt_rays = 60.0 / (SCREEN_WIDTH -  1.0) * 1.0;
	data->ray_angle = 0.0f;
}

void	init_data(t_data *data, char **map)
{
	data->map = map;
	data->Px = 3.0;
	data->Py = 3.0;
	data->map[(int)data->Py][(int)data->Px] = 'N';
	data->distance_screen = (SCREEN_WIDTH * 0.5) / tanf(to_radian(FOV * 0.5));
	get_angles(data);
	data->Px = data->Px + 0.5;
	data->Py = data->Py + 0.5;
}

int	init_display(char **map)
{
	t_data	data;

	init_data(&data, map);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	 	return (1);
	data.img.ptr = mlx_new_image(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data.img.ptr)
		return (1);
	data.img.addr = mlx_get_data_addr(data.img.ptr, &data.img.bpp, &data.img.length, &data.img.endian);
	if (!data.img.addr)
	{
		mlx_destroy_image(data.mlx_ptr, data.img.ptr);
		return (1);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!data.win_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}
	mlx_loop_hook(data.mlx_ptr, &raycasting, &data);
	mlx_hook(data.win_ptr, 2, 1L<<0, &keys, &data);
	mlx_hook(data.win_ptr, 17, 0, &close_win, &data);
	mlx_loop(data.mlx_ptr);
	clean_display(&data);
	return (0);
}
