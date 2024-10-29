/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:10:09 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/29 11:12:49 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	save_start(t_parser *map, t_co _it)
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

static bool	find_player(t_parser *map)
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
					return (perr(0, "Error: too many players"), false);
				save_start(map, it);
			}
			it.j++;
		}
		it.i++;
	}
	return (map->found_p);
}

bool	f_is_valid(t_parser *map)
{
	if (!find_player(map))
		return (perr(0, "Error: invalid player start position"), false);
	if (!sqalloc_map(map))
		return (perr(errno, "when allocating square map"), false);
	if (!iwall(*map))
		return (perr(0, "Error: open map"), false);
	return (true);
}
