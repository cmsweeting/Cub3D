/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:13:36 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/07 17:48:28 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	rgb_to_int(t_map *map, char **rgb, bool floor)
{
	size_t	i;

	i = 0;
	if (!rgb_is_valid(rgb))
		return (false);
	while (rgb[i])
	{
		if (floor)
		{
			map->fcolor[i] = ft_atoi(rgb[i]);
			if (map->fcolor[i] < 0 || map->fcolor[i] > 255)
				return (verror(strerror(EINVAL), ": invalid RGB value: ", \
				rgb[i]), false);
		}
		else
		{
			map->ccolor[i] = ft_atoi(rgb[i]);
			if (map->ccolor[i] < 0 || map->ccolor[i] > 255)
				return (verror(strerror(EINVAL), ": invalid RGB value: ", \
				rgb[i]), false);
		}
		i++;
	}
	return (true);
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
			if (!is_texture(map, rfile[i]))
				return (false);
			else if (!is_color(map, rfile[i]))
				return (false);
			else if (is_map(rfile[i]))
				break ;
		}
		i++;
	}
	if (map->allt_found != 6)
		return (print_error(0, "Error: missing texture"), false);
	return (true);
}
