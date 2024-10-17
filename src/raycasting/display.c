/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:29 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/17 15:50:07 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	clean_display(t_ray *rdata)
{
	mlx_destroy_image(rdata->mlx.mlx, rdata->img.ptr);
	mlx_destroy_window(rdata->mlx.mlx, rdata->mlx.win);
	rdata->mlx.win = NULL;
	mlx_destroy_display(rdata->mlx.mlx);
	free(rdata->mlx.mlx);
}

void	get_angles(t_ray *rdata, t_card pcard)
{
	if (pcard == EA)
		rdata->c_angle = 0.0;
	else if (pcard == NO)
		rdata->c_angle = 90.0;
	else if (pcard == WE)
		rdata->c_angle = 180.0;
	else if (pcard == SO)
		rdata->c_angle = 270.0;
	rdata->rayspacing = 60.0 / (S_WIDTH - 1.0);
}

void	init_data(t_ray *rdata)
{
	rdata->p.x = (double)rdata->map.p.j + 0.5;
	rdata->p.y = (double)rdata->map.p.i + 0.5;
	rdata->d_screen = (S_WIDTH * 0.5) / tanf(to_radian(FOV * 0.5));
	get_angles(rdata, rdata->map.pcard);
}

int	init_display(t_ray *rdata)
{
	init_data(rdata);
	rdata->mlx.mlx = mlx_init();
	if (!rdata->mlx.mlx)
		return (1);
	rdata->img.ptr = mlx_new_image(rdata->mlx.mlx, S_WIDTH, S_HEIGHT);
	if (!rdata->img.ptr)
		return (1);
	rdata->img.xpm_data = mlx_get_data_addr(rdata->img.ptr, &rdata->img.bpp, \
					&rdata->img.len, &rdata->img.endian);
	if (!rdata->img.xpm_data)
	{
		mlx_destroy_image(rdata->mlx.mlx, rdata->img.ptr);
		return (1);
	}
	rdata->mlx.win = mlx_new_window(rdata->mlx.mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	if (!rdata->mlx.win)
	{
		mlx_destroy_image(rdata->mlx.mlx, rdata->img.ptr);
		mlx_destroy_display(rdata->mlx.mlx);
		free(rdata->mlx.mlx);
		return (1);
	}
	return (0);
}

void	run_game(t_ray *rdata)
{
	mlx_loop_hook(rdata->mlx.mlx, &raycasting, rdata);
	mlx_hook(rdata->mlx.win, 2, 1L << 0, &keys, rdata);
	mlx_hook(rdata->mlx.win, 17, 0, &close_win, rdata);
	mlx_loop(rdata->mlx.mlx);
	clean_display(rdata);
}
