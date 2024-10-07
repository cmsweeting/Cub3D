/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:24:31 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/07 17:48:37 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	str_is_num(char	*str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_strlen(str) == 1)
			if (str[i] < '0' || str[i] > '9')
				return (false);
		if ((str[i] != '\n' && (str[i] < '0' || str[i] > '9')))
			return (false);
		i++;
	}
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

bool	rgb_is_valid(char **rgb)
{
	size_t	i;

	i = 0;
	if (ft_arrlen(rgb) != 3)
		return (print_error(EINVAL, "missing RGB value"), false);
	while (rgb[i])
	{
		if (ft_strlen(rgb[i]) > 3 || !str_is_num(rgb[i]))
			return (verror(strerror(EINVAL), ": invalid RGB value: ", \
			rgb[i]), false);
		i++;
	}
	return (true);
}

bool	is_map(char *str)
{
	size_t	i;

	i = 0;
	if (!str && !str[i])
		return (false);
	while (str[i])
	{
		if (str[i] == '0' || str[i] == '1')
		{
			printf("%s", str);
			return (true);
		}
		i++;
	}
	return (false);
}
