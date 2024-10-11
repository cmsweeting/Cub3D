/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:29 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/11 15:11:07 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	get_angles(t_data *data)
{
	if (data->map[(int)data->Py][(int)data->Px] == 'E')
		data->P_angle = 0.0f;
	else if (data->map[(int)data->Py][(int)data->Px] == 'N')
		data->P_angle = 90.0f;//PI * 0.5f;
	else if (data->map[(int)data->Py][(int)data->Px] == 'W')
		data->P_angle = 180.0f;//PI;
	else if (data->map[(int)data->Py][(int)data->Px] == 'S')
		data->P_angle = 270.0f;//1.5f * PI;
	data->angle_bt_rays = 60.0 / (SCREEN_WIDTH -  1.0f) * 1.0f;
	// printf("p angle : %f\n", data->P_angle);
}

void	init_data(t_data *data, char **map)
{
	float	half_fov_radian;

	data->left = true;
	data->map = map;
	data->Px = 2.0f;
	data->Py = 5.0f;
	data->map[(int)data->Py][(int)data->Px] = 'N';
	half_fov_radian = (FOV / 2) * (PI / 180) * 1.0f;
	data->distance_screen = (SCREEN_WIDTH / 2) / tanf(half_fov_radian)* 1.0f;
	get_angles(data);
	data->Px = (data->Px * CUB) + (CUB / 2);
	data->Py = (data->Py * CUB) + (CUB / 2);
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
	// mlx_loop_hook(data.mlx_ptr, &raycasting, &data);
	mlx_hook(data.win_ptr, 2, 1L<<0, &keys, &data);
	mlx_hook(data.win_ptr, 17, 0, &close_win, &data);
	mlx_loop(data.mlx_ptr);
	clean_display(&data);
	return (0);
}
