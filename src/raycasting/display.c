/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:29 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/18 21:51:29 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D.h"

void	clean_display(t_ray *r)
{
	if (r->win)
		mlx_destroy_window(r->mlx, r->win);
	r->win = NULL;
	if (r->mlx)
		mlx_destroy_display(r->mlx);
	free(r->mlx);
}

static void	get_angles(t_ray *r, t_card pcard)
{
	if (pcard == EA)
		r->c_angle = 0.0;
	else if (pcard == NO)
		r->c_angle = 90.0;
	else if (pcard == WE)
		r->c_angle = 180.0;
	else if (pcard == SO)
		r->c_angle = 270.0;
	r->rayspacing = 60.0 / (S_WIDTH - 1.0);
}

static void	init_data(t_ray *r)
{
	r->map.msize.i -= 1;
	r->map.msize.j -= 1;
	r->p.x = (double)r->map.p.j + 0.5;
	r->p.y = (double)r->map.p.i + 0.5;
	r->hs_width = S_WIDTH * 0.5;
	r->d_screen = r->hs_width / tan(radian(FOV * 0.5));
	get_angles(r, r->map.pcard);
}

int	init_display(t_ray *r)
{
	init_data(r);
	r->mlx = mlx_init();
	if (!r->mlx)
		return (1);
	if (!create_images(r))
		return (1);
	if (!get_xpmstr(r))
		return (1);
	r->win = mlx_new_window(r->mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	if (!r->win)
		return (1);
	return (0);
}

void	run_game(t_ray *r)
{
	mlx_loop_hook(r->mlx, &raycasting, r);
	mlx_hook(r->win, 2, 1L << 0, &key_press, r);
	mlx_hook(r->win, 3, 1L << 1, &key_release, r);
	mlx_hook(r->win, 17, 0, &close_win, r);
	mlx_loop(r->mlx);
}
