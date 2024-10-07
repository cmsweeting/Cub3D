/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:17:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/07 13:31:38 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_map(t_map *map)
{
	if (map->no_texture)
		free(map->no_texture);
	if (map->so_texture)
		free(map->so_texture);
	if (map->we_texture)
		free(map->we_texture);
	if (map->ea_texture)
		free(map->ea_texture);
}

static void	init_map(t_map *map)
{
	size_t	i;

	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->allt_found = 0;
	map->map_start = false;
	i = 0;
	while (i < 3)
	{
		map->fcolor[i] = 0;
		map->ccolor[i] = 0;
		i++;
	}
}

static void	print_map(t_map map)
{
	printf("%s", map.ea_texture);
	printf("%s", map.we_texture);
	printf("%s", map.no_texture);
	printf("%s", map.so_texture);
	printf("\n");
	printf("floor color:	%d	|	%d	|	%d\n", map.fcolor[0], \
	map.fcolor[1], map.fcolor[2]);
	printf("celling color:	%d	|	%d	|	%d\n", map.ccolor[0], \
	map.ccolor[1], map.ccolor[2]);
}

int	main(int ac, char *av[])
{
	t_map	map;

	if (ac != 2)
		return (print_error(EINVAL, "expected one argument"), EINVAL);
	init_map(&map);
	if (!fetch_map(av[1], &map))
		return (free_map(&map), EINVAL);
	print_map(map);
	free_map(&map);
}
