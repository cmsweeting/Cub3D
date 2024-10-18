/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:43:19 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/18 11:21:47 by cdomet-d         ###   ########.fr       */
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

static bool	is_path(t_parser *fdata, char *str)
{
	if (ft_strncmp("NO ", str, 3) == 0)
	{
		fdata->allt_found += 1;
		fdata->no.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (fdata->no.pto_file);
	}
	if (ft_strncmp("SO ", str, 3) == 0)
	{
		fdata->allt_found += 1;
		fdata->so.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (fdata->so.pto_file);
	}
	if (ft_strncmp("WE ", str, 3) == 0)
	{
		fdata->allt_found += 1;
		fdata->we.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (fdata->we.pto_file);
	}
	if (ft_strncmp("EA ", str, 3) == 0)
	{
		fdata->allt_found += 1;
		fdata->ea.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (fdata->ea.pto_file);
	}
	return (true);
}

static bool	is_color(t_parser *fdata, char *str)
{
	char	**rgb;

	rgb = NULL;
	if (ft_strncmp("F ", str, 2) == 0)
	{
		rgb = ft_split(skip_whitespaces(&str[1]), ',');
		if (!rgb)
			return (perr(errno, "while retrieving RGB colors"), false);
		if (!rgb_to_int(fdata, rgb, true))
			return (free_dtab(rgb), false);
		fdata->allt_found += 1;
	}
	if (ft_strncmp("C ", str, 2) == 0)
	{
		rgb = ft_split(skip_whitespaces(&str[1]), ',');
		if (!rgb)
			return (perr(errno, "while retrieving RGB colors"), false);
		if (!rgb_to_int(fdata, rgb, false))
			return (free_dtab(rgb), false);
		fdata->allt_found += 1;
	}
	free_dtab(rgb);
	return (true);
}

bool	get_values(t_parser *fdata, char **rfile)
{
	size_t	i;

	i = 0;
	while (rfile[i])
	{
		if (rfile[i][0] != '\n')
		{
			if (fdata->allt_found > 6)
				return (perr(0, "Error: extra texture"), false);
			if (!is_path(fdata, rfile[i]))
				return (perr(0, "Error: invalid texture"), false);
			if (!is_color(fdata, rfile[i]))
				return (false);
			if (is_map(rfile[i]))
			{
				if (!cpy_fdata(fdata, rfile, i))
					return (perr(errno, "while retrieving map"), false);
				break ;
			}
		}
		i++;
	}
	return (found_all_elements(*fdata));
}
