/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:10:09 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/14 17:02:02 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	reset_map(t_map *map)
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
			it.j++;
		}
		it.i++;
	}
	if (map->pcard == WE)
		map->map[map->p.i][map->p.j] = 'W';
	if (map->pcard == NO)
		map->map[map->p.i][map->p.j] = 'N';
	if (map->pcard == EA)
		map->map[map->p.i][map->p.j] = 'E';
	if (map->pcard == SO)
		map->map[map->p.i][map->p.j] = 'S';
}

static void	save_start(t_map *map, t_co _it)
{
	map->p.i = _it.i;
	map->p.j = _it.j;
	map->found_p = true;
	if (map->map[_it.i][_it.j] == 'W')
		map->pcard = WE;
	else if (map->map[_it.i][_it.j] == 'S')
		map->pcard = SO;
	else if (map->map[_it.i][_it.j] == 'N')
		map->pcard = NO;
	else if (map->map[_it.i][_it.j] == 'E')
		map->pcard = EA;
	map->map[_it.i][_it.j] = '0';
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
			if (map->map[it.i][it.j] == 'N' || map->map[it.i][it.j] == 'S' || \
			map->map[it.i][it.j] == 'E' || map->map[it.i][it.j] == 'W')
			{
				if (map->found_p == true)
					return (false);
				save_start(map, it);
			}
			it.j++;
		}
		it.i++;
	}
	return (map->found_p);
}

bool	map_is_valid(t_map *map)
{
	bool	wismissing;

	wismissing = false;
	if (!find_player(map))
		return (print_error(0, "Error: invalid player start position"), false);
	sqalloc_map(map);
	printf("%ld, %ld, %ld\n", map->msize.i, map->msize.j, map->msize.i * map->msize.j);
	if (!iwall(*map))
	{
		// print_darr(map->map, false);
		return (print_error(0, "Error: invalid map"), false);
	}
	// print_darr(map->map, false);
	reset_map(map);
	return (true);
}
