/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:24:31 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/25 11:44:48 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_invalid_char(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i] == '\n')
		return (true);
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = '0';
		if (str[i] != '1' && str[i] != '0' && str[i] != 'N' \
		&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W' && str[i] != '\n')
			return (true);
		i++;
	}
	return (false);
}

bool	is_element(char *str)
{
	if (ft_strncmp(str, "NO ", 3) == 0 || \
	ft_strncmp(str, "SO ", 3) == 0 || \
	ft_strncmp(str, "WE ", 3) == 0 || \
	ft_strncmp(str, "EA ", 3) == 0 || \
	ft_strncmp("F ", str, 2) == 0 || \
	ft_strncmp("C ", str, 2) == 0 || \
	str[0] == '\n')
		return (true);
	return (false);
}

size_t	max_len(char **map)
{
	size_t	i;
	size_t	max;
	size_t	len;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

bool	found_all_elements(t_parser map)
{
	if ((map.allt_found < 6) || !map.ea.pto_file || !map.no.pto_file || \
	!map.so.pto_file || !map.we.pto_file || !map.map)
		return (perr(0, "Error: missing element"), false);
	return (true);
}

char	*skip_whitespaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (&str[i]);
}
