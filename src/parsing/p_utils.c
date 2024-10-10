/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:24:31 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/10 18:07:23 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_invalid_char(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i] == '\n')
		return (true);
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != ' ' && str[i] != 'N' \
		&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W' && str[i] != '\n')
			return (true);
		i++;
	}
	return (false);
}

bool	is_texture(char *str)
{
	if (ft_strncmp(str, "NO ", 3) == 0 || \
	ft_strncmp(str, "SO ", 3) == 0 || \
	ft_strncmp(str, "WE ", 3) == 0 || \
	ft_strncmp(str, "EA ", 3) == 0 || \
	ft_strncmp("F ", str, 2) == 0 || \
	ft_strncmp("C ", str, 2) == 0)
		return (true);
	return (false);
}

bool	cpy_map(t_map *map, char **rfile, size_t i)
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

bool	found_all_elements(t_map map)
{
	if ((map.allt_found < 6) || !map.ea_texture || !map.no_texture || \
	!map.so_texture || !map.we_texture || !map.map)
		return (print_error(0, "Error: missing element"), false);
	return (true);
}

char	*skip_whitespaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	return (&str[i]);
}
