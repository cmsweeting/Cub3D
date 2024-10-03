/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:13:36 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/03 17:47:18 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*skip_whitespaces(char *str)
{
	size_t	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (&str[i]);
}

static bool	is_texture(t_map *map, char *str)
{
	if (ft_strncmp(skip_whitespaces(str), "NO ", 3) == 0)
	{
		map->allt_found += 1;
		map->no_texture = ft_strdup(skip_whitespaces(&str[3]));
		return (map->no_texture);
	}
	if (ft_strncmp(str, "SO ", 3) == 0)
	{
		map->allt_found += 1;
		map->so_texture = ft_strdup(skip_whitespaces(&str[3]));
		return (map->so_texture);
	}
	if (ft_strncmp(str, "WE ", 3) == 0)
	{
		map->allt_found += 1;
		map->we_texture = ft_strdup(skip_whitespaces(&str[3]));
		return (map->we_texture);
	}
	if (ft_strncmp(str, "EA ", 3) == 0)
	{
		map->allt_found += 1;
		map->ea_texture = ft_strdup(skip_whitespaces(&str[3]));
		return (map->ea_texture);
	}
	return (true);
}

// static bool	is_color(char *str)
// {
// 	if (ft_strncmp("F", str, 2) == 0)
// 		return (true);
// 	if (ft_strncmp("C", str, 2) == 0)
// 		return (true);
// 	return (false);
// }

bool	get_values(t_map *map, char **rfile)
{
	size_t	i;

	i = 0;
	while (rfile[i])
	{
		if (rfile[i][0] != '\n')
		{
			if (!is_texture(map, rfile[i]))
				return (false);
		}
		i++;
	}
	printf("%d\n", map->allt_found);
	if (map->allt_found != 4)
		return (false);
	return (true);
}
