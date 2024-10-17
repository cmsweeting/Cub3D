/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parser_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:13:36 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/15 17:04:57 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		fdata->no_texture = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (fdata->no_texture);
	}
	if (ft_strncmp("SO ", str, 3) == 0)
	{
		fdata->allt_found += 1;
		fdata->so_texture = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (fdata->so_texture);
	}
	if (ft_strncmp("WE ", str, 3) == 0)
	{
		fdata->allt_found += 1;
		fdata->we_texture = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (fdata->we_texture);
	}
	if (ft_strncmp("EA ", str, 3) == 0)
	{
		fdata->allt_found += 1;
		fdata->ea_texture = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (fdata->ea_texture);
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
			return (print_error(errno, "while retrieving RGB colors"), false);
		if (!rgb_to_int(fdata, rgb, true))
			return (free_dtab(rgb), false);
		fdata->allt_found += 1;
	}
	if (ft_strncmp("C ", str, 2) == 0)
	{
		rgb = ft_split(skip_whitespaces(&str[1]), ',');
		if (!rgb)
			return (print_error(errno, "while retrieving RGB colors"), false);
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
				return (print_error(0, "Error: extra texture"), false);
			if (!is_path(fdata, rfile[i]))
				return (print_error(0, "Error: invalid texture"), false);
			if (!is_color(fdata, rfile[i]))
				return (false);
			if (is_map(rfile[i]))
			{
				if (!cpy_fdata(fdata, rfile, i))
					return (print_error(errno, "while retrieving map"), false);
				break ;
			}
		}
		i++;
	}
	return (found_all_elements(*fdata));
}
