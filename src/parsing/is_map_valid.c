/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:10:09 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/10 10:40:38 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool find_player(t_map *map)
{
	t_co it;

	it.i = 0;
	while (map->map[it.i])
	{
		it.j = 0;
		while(map->map[it.i][it.j])
		{
			if (map->map[it.i][it.j] == ' ')
				map->map[it.i][it.j] = '0';
			if (map->map[it.i][it.j] == 'N' || map->map[it.i][it.j] == 'S'|| \
			map->map[it.i][it.j] == 'E' || map->map[it.i][it.j] == 'W')
			{
				if (map->found_p == true)
					return (print_error(0, "Error: duplicate player starting point"), false);
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


// void	is_sprite_trapped(char **map, size_t i, size_t j)
// {
// 	while (map[i][j] != '1' && map[i][j] != 'v')
// 	{
// 		if (map[i][j] == 'E')
// 		{
// 			map[i][j] = 'v';
// 			return ;
// 		}
// 		map[i][j] = 'v';
// 		is_sprite_trapped(map, i + 1, j);
// 		is_sprite_trapped(map, i - 1, j);
// 		is_sprite_trapped(map, i, j + 1);
// 		is_sprite_trapped(map, i, j - 1);
// 	}
// }


static void	has_walls(size_t i, size_t j, char **map)
{
	if (map[i][j] == '0' && (i == 0 || i == ft_arrlen(map)) && (j == 0 || j == ft_strlen(map[i])))
		return;
	else if (map[i][j] == 'x')
		return;
	print_darr(map, false);
	printf("%ld || %ld\n", i, j);
	printf("\n");
	map[i][j] = 'x';
	if (map[i + 1][j])
		has_walls(i + 1, j, map);
	if (map[i - 1][j])
		has_walls(i - 1, j, map);
	has_walls(i, j + 1, map);
	has_walls(i, j - 1, map);
}
bool	map_is_valid(t_map *map)
{
	if(!find_player(map))
		return (print_error(0, "Error: missing player starting point"), false);
	has_walls(map->p.i, map->p.j, map->map);
	return (true);
}
