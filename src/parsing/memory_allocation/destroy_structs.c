/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:14:28 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/18 11:20:39 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_fdata(t_parser *map)
{
	if (map->no.pto_file)
		free(map->no.pto_file);
	if (map->no.pto_file)
		free(map->so.pto_file);
	if (map->we.pto_file)
		free(map->we.pto_file);
	if (map->ea.pto_file)
		free(map->ea.pto_file);
	free_dtab(map->map);
}

void	free_rdata(t_ray *ray)
{
	if (ray->map.ea.ptr)
		mlx_destroy_image(ray->mlx, ray->map.ea.ptr);
	if (ray->map.so.ptr)
		mlx_destroy_image(ray->mlx, ray->map.so.ptr);
	if (ray->map.we.ptr)
		mlx_destroy_image(ray->mlx, ray->map.we.ptr);
	if (ray->map.no.ptr)
		mlx_destroy_image(ray->mlx, ray->map.no.ptr);
	if (ray->img.ptr)
		mlx_destroy_image(ray->mlx, ray->img.ptr);
	clean_display(ray);
}

void	dall(t_parser *map, t_ray *ray)
{
	free_fdata(map);
	free_rdata(ray);
}