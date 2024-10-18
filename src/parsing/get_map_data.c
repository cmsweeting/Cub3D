/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:43:19 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/18 21:52:05 by cdomet-d         ###   ########lyon.fr   */
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

static bool	is_path(t_parser *f, char *str)
{
	if (ft_strncmp("NO ", str, 3) == 0)
	{
		f->allt_found += 1;
		f->no.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (f->no.pto_file);
	}
	if (ft_strncmp("SO ", str, 3) == 0)
	{
		f->allt_found += 1;
		f->so.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (f->so.pto_file);
	}
	if (ft_strncmp("WE ", str, 3) == 0)
	{
		f->allt_found += 1;
		f->we.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (f->we.pto_file);
	}
	if (ft_strncmp("EA ", str, 3) == 0)
	{
		f->allt_found += 1;
		f->ea.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (f->ea.pto_file);
	}
	return (true);
}

static bool	is_color(t_parser *f, char *str)
{
	char	**rgb;

	rgb = NULL;
	if (ft_strncmp("F ", str, 2) == 0)
	{
		rgb = ft_split(skip_whitespaces(&str[1]), ',');
		if (!rgb)
			return (perr(errno, "while retrieving RGB colors"), false);
		if (!rgb_to_int(f, rgb, true))
			return (free_dtab(rgb), false);
		f->allt_found += 1;
	}
	if (ft_strncmp("C ", str, 2) == 0)
	{
		rgb = ft_split(skip_whitespaces(&str[1]), ',');
		if (!rgb)
			return (perr(errno, "while retrieving RGB colors"), false);
		if (!rgb_to_int(f, rgb, false))
			return (free_dtab(rgb), false);
		f->allt_found += 1;
	}
	free_dtab(rgb);
	return (true);
}

bool	get_values(t_parser *f, char **rfile)
{
	size_t	i;

	i = 0;
	while (rfile[i])
	{
		if (rfile[i][0] != '\n')
		{
			if (f->allt_found > 6)
				return (perr(0, "Error: extra texture"), false);
			if (!is_path(f, rfile[i]))
				return (perr(0, "Error: invalid texture"), false);
			if (!is_color(f, rfile[i]))
				return (false);
			if (is_map(rfile[i]))
			{
				if (!cpy_f(f, rfile, i))
					return (perr(errno, "while retrieving map"), false);
				break ;
			}
		}
		i++;
	}
	return (found_all_elements(*f));
}
