/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:10:09 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/10 18:09:28 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static size_t	max_len(char **map)
{
	size_t	i;
	size_t	max;
	size_t	len;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static bool	clean_map(t_map *map)
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

static bool	find_player(t_map *map)
{
	t_co	it;

	it.i = 0;
	while (map->map[it.i])
	{
		it.j = 0;
		while (map->map[it.i][it.j])
		{
			if (map->map[it.i][it.j] == ' ')
				map->map[it.i][it.j] = '0';
			if (map->map[it.i][it.j] == 'N' || map->map[it.i][it.j] == 'S' || \
			map->map[it.i][it.j] == 'E' || map->map[it.i][it.j] == 'W')
			{
				if (map->found_p == true)
					return (print_error(0, "Error: duplicate player starting \
					 point"), false);
				map->p.i = it.i;
				map->p.j = it.j;
				map->found_p = true;
			}
			it.j++;
		}
		it.i++;
	}
	return (map->found_p);
}

static void	has_walls(size_t i, size_t j, t_map *map)
{
	if (map->map[i][j] == 'S')
		map->map[i][j] = '0';
	if (i == 0 || i == (map->msize.i - 1) || \
	j == 0 || (j == map->msize.j -1) || map->map[i][j] != '0')
	{
		if (map->map[i][j] == '0')
		{
			map->mnot_enclosed = true;
			return ;
		}
		return ;
	}
	map->map[i][j] = ' ';
	has_walls(i + 1, j, map);
	has_walls(i - 1, j, map);
	has_walls(i, j + 1, map);
	has_walls(i, j - 1, map);
}

//TODO: don't send the whole struct as a pointer to avoid value modification
bool	map_is_valid(t_map *map)
{
	if (!find_player(map))
		return (print_error(0, "Error: missing player starting point"), false);
	clean_map(map);
	has_walls(map->p.i, map->p.j, map);
	if (map->mnot_enclosed)
		return (print_error(0, "Error: map is not enclosed"), false);
	print_darr(map->map, false);
	return (true);
}
