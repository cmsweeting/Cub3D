/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:52:15 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/25 18:36:08 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_collisions(double x, double y, t_ray *r)
{
	ssize_t	i;
	ssize_t	j;

	i = (ssize_t)y;
	j = (ssize_t)x;
	if (i < 0 || j < 0 || i > r->map.msize.i || j > r->map.msize.j \
		|| !r->map.map[i][j])
		return (-1);
	if (r->map.map[i][j] == '1')
		return (1);
	return (0);
}

int	find_wall(t_ray *r, t_point *pt, t_point *step)
{
	int	i;

	i = check_collisions(pt->x, pt->y, r);
	while (!i)
	{
		pt->x += step->x;
		pt->y += step->y;
		i = check_collisions(pt->x, pt->y, r);
	}
	return (i);
}
