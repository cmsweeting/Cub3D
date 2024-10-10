/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:31:22 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/09 14:37:27 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	extract_file(int _fd, char ***rfile)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 1;
	*rfile = malloc((size + 1) * sizeof(char *));
	if (!*rfile)
		return (false);
	(*rfile)[size] = NULL;
	(*rfile)[i] = get_next_line(_fd);
	if (errno)
		return (free_dtab(*rfile), false);
	while ((*rfile)[i])
	{
		size++;
		if (!ft_realloc(size, rfile))
			return (free_dtab(*rfile), false);
		i++;
		(*rfile)[i] = get_next_line(_fd);
		if (errno)
			return (free_dtab(*rfile), false);
	}
	return (true);
}

static bool	ext_is_valid(char *arg)
{
	size_t	i;

	i = ft_strlen(arg) - 4;
	if (ft_strncmp(&arg[i], ".cub", 5) == 0)
		return (true);
	return (false);
}

static bool	open_file(char *arg, char ***rfile)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (print_error(errno, "could not open file"), false);
	if (!extract_file(fd, rfile))
		return (close(fd), print_error(errno, "during file extraction"), false);
	close (fd);
	return (true);
}

bool	fill_struct(char *arg, t_map *_map)
{
	char	**rfile;

	rfile = NULL;
	if (!arg)
		return (print_error(EINVAL, "expected file, got NULL pointer"), false);
	if (!ext_is_valid(arg))
		return (print_error(EINVAL, "extension should be .cub"), false);
	if (!open_file(arg, &rfile))
		return (false);
	if (!get_values(_map, rfile))
		return (free_dtab(rfile), print_error(errno, "while processing \
		file data"), false);
	free_dtab(rfile);
	return (true);
}
