/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:13:36 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/10 18:06:31 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_map(char *str)
{
	size_t	i;

	i = 0;
	if (!str && !str[i])
		return (false);
	if (is_texture(str))
		return (false);
	while (str[i])
	{
		if (str[i] == '0' || str[i] == '1')
			return (true);
		i++;
	}
	return (false);
}

//TODO: fix invalid read of size when when texture key is found but path is 
// not on the same line

/* for input
WE 
./path_to_the_west_texture
==46801== Invalid read of size 1
==46801==    at 0x40375C: ft_strtrim (in /home/cdomet-d/Documents/WIP/Cub3D/)
==46801==    by 0x401ACB: is_path (get_map_data.c:50)*/

static bool	is_path(t_map *map, char *str)
{
	if (ft_strncmp("NO ", str, 3) == 0)
	{
		map->allt_found += 1;
		map->no_texture = ft_strtrim(skip_whitespaces(&str[3]), "\n");
		return (map->no_texture);
	}
	if (ft_strncmp("SO ", str, 3) == 0)
	{
		map->allt_found += 1;
		map->so_texture = ft_strtrim(skip_whitespaces(&str[3]), "\n");
		return (map->so_texture);
	}
	if (ft_strncmp("WE ", str, 3) == 0)
	{
		map->allt_found += 1;
		map->we_texture = ft_strtrim(skip_whitespaces(&str[3]), "\n");
		return (map->we_texture);
	}
	if (ft_strncmp("EA ", str, 3) == 0)
	{
		map->allt_found += 1;
		map->ea_texture = ft_strtrim(skip_whitespaces(&str[3]), "\n");
		return (map->ea_texture);
	}
	return (true);
}

static bool	is_color(t_map *map, char *str)
{
	char	**rgb;

	rgb = NULL;
	if (ft_strncmp("F ", str, 2) == 0)
	{
		rgb = ft_split(skip_whitespaces(&str[1]), ',');
		if (!rgb)
			return (print_error(errno, "while retrieving RGB colors"), false);
		if (!rgb_to_int(map, rgb, true))
			return (free_dtab(rgb), false);
		map->allt_found += 1;
	}
	if (ft_strncmp("C ", str, 2) == 0)
	{
		rgb = ft_split(skip_whitespaces(&str[1]), ',');
		if (!rgb)
			return (print_error(errno, "while retrieving RGB colors"), false);
		if (!rgb_to_int(map, rgb, false))
			return (free_dtab(rgb), false);
		map->allt_found += 1;
	}
	free_dtab(rgb);
	return (true);
}

bool	get_values(t_map *map, char **rfile)
{
	size_t	i;

	i = 0;
	while (rfile[i])
	{
		if (rfile[i][0] != '\n')
		{
			if (map->allt_found > 6)
				return (print_error(0, "Error: extra texture"), false);
			if (!is_path(map, rfile[i]))
				return (false);
			if (!is_color(map, rfile[i]))
				return (false);
			if (is_map(rfile[i]))
			{
				if (!cpy_map(map, rfile, i))
					return (print_error(errno, "while retrieving map"), false);
				break ;
			}
		}
		i++;
	}
	return (found_all_elements(*map));
}
