/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:29 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/17 17:29:40 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D.h"

void	clean_display(t_ray *rdata)
{
	if (rdata->win)
		mlx_destroy_window(rdata->mlx, rdata->win);
	rdata->win = NULL;
	if (rdata->mlx)
		mlx_destroy_display(rdata->mlx);
	free(rdata->mlx);
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

int	init_display(t_ray *rdata, t_parser fdata)
{
	init_data(rdata);
	rdata->mlx = mlx_init();
	if (!rdata->mlx)
		return (1);
	if (!create_images(rdata, fdata))
		return (1);
	rdata->img.strxpm = mlx_get_data_addr(rdata->img.ptr, &rdata->img.bpp, \
					&rdata->img.len, &rdata->img.endian);
	if (!rdata->img.strxpm)
	{
		mlx_destroy_image(rdata->mlx, rdata->img.ptr);
		return (1);
	}
	rdata->win = mlx_new_window(rdata->mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	if (!rdata->win)
	{
		mlx_destroy_display(rdata->mlx);
		free(rdata->mlx);
		return (1);
	}
	return (0);
}

void	run_game(t_ray *rdata)
{
	mlx_loop_hook(rdata->mlx, &raycasting, rdata);
	mlx_hook(rdata->win, 2, 1L << 0, &keys, rdata);
	mlx_hook(rdata->win, 17, 0, &close_win, rdata);
	mlx_loop(rdata->mlx);
}
