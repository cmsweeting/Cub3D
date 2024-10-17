/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:07:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/17 17:11:31 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	ft_realloc(size_t size, char ***arr)
{
	char	**copy;
	size_t	i;

	i = 0;
	copy = malloc((size + 1) * sizeof(char *));
	if (!copy)
		return (false);
	copy[size] = NULL;
	while ((*arr) && (*arr)[i])
	{
		copy[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	*arr = copy;
	return (true);
}

bool	sqalloc_map(t_parser *map)
{
	t_co	it;
	char	**cmap;

	it.i = 0;
	map->msize.i = ft_arrlen(map->map);
	cmap = malloc((map->msize.i + 1) * sizeof(char *));
	if (!cmap)
		return (false);
	cmap[map->msize.i] = NULL;
	map->msize.j = max_len(map->map);
	while (map->map[it.i])
	{
		cmap[it.i] = malloc((map->msize.j + 1) * sizeof(char));
		if (!cmap)
			return (free_dtab(cmap), false);
		cmap[it.i][map->msize.j] = '\0';
		ft_strlcpy(cmap[it.i], map->map[it.i], map->msize.j + 1);
		it.j = ft_strlen(map->map[it.i]);
		while (it.j < map->msize.j)
			cmap[it.i][it.j++] = '0';
		it.i++;
	}
	free_dtab(map->map);
	map->map = cmap;
	return (true);
}

bool	cpy_fdata(t_parser *map, char **rfile, size_t i)
{
	size_t	size;
	size_t	j;

	j = 0;
	size = 1;
	while (rfile[i])
	{
		if (is_invalid_char(rfile[i]))
			return (verror("In map:", " forbidden char at ", rfile[i]), false);
		if (!ft_realloc(size, &map->map))
			return (free_dtab(map->map), false);
		size++;
		map->map[j] = ft_strtrim(rfile[i], "\n");
		if (!map->map[j])
			return (false);
		i++;
		j++;
	}
	return (true);
}

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
