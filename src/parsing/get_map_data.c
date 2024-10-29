/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:43:19 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/29 11:17:49 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	elemf(unsigned char *allf)
{
	*allf += 1;
}

bool	is_map(char *str)
{
	size_t	i;

	i = 0;
	if (!str && !str[i])
		return (false);
	while (str[i])
	{
		if (str[i] == '0' || str[i] == '1' || str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

static bool	is_path(t_parser *f, char *str)
{
	if (ft_strncmp("NO ", str, 3) == 0)
	{
		if (!f->no.pto_file)
			f->no.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (elemf(&f->alle_found), f->no.pto_file);
	}
	if (ft_strncmp("SO ", str, 3) == 0)
	{
		if (!f->so.pto_file)
			f->so.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (elemf(&f->alle_found), f->so.pto_file);
	}
	if (ft_strncmp("WE ", str, 3) == 0)
	{
		if (!f->we.pto_file)
			f->we.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (elemf(&f->alle_found), f->we.pto_file);
	}
	if (ft_strncmp("EA ", str, 3) == 0)
	{
		if (!f->ea.pto_file)
			f->ea.pto_file = ft_strtrim(skip_whitespaces(&str[2]), "\n");
		return (elemf(&f->alle_found), f->ea.pto_file);
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
		f->alle_found += 1;
		f->floor = int_to_hex(f->fcolor);
	}
	if (ft_strncmp("C ", str, 2) == 0)
	{
		rgb = ft_split(skip_whitespaces(&str[1]), ',');
		if (!rgb)
			return (perr(errno, "while retrieving RGB colors"), false);
		if (!rgb_to_int(f, rgb, false))
			return (free_dtab(rgb), false);
		f->alle_found += 1;
		f->ceiling = int_to_hex(f->ccolor);
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
		if (f->alle_found > 6)
			return (perr(0, "Error: extra element"), false);
		if (is_element(rfile[i]))
		{
			if (!is_path(f, rfile[i]))
				return (perr(0, "Error: invalid texture"), false);
			else if (!is_color(f, rfile[i]))
				return (false);
		}
		else if (is_map(rfile[i]))
		{
			if (!found_all_elements(*f, false))
				return (false);
			return (cpy_f(f, rfile, i));
		}
		else
			return (perr(EINVAL, rfile[i]), false);
		i++;
	}
	return (found_all_elements(*f, true));
}
