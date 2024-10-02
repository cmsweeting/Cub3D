/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:31:22 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/02 16:35:37 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void print_darr(char **arr)
// {
// 	size_t	i;

// 	i = 0;
// 	while (arr[i])
// 	{	
// 		printf("arr[%ld]: %s", i, arr[i]);
// 		i++;
// 	}
// }
static bool resize_arr(size_t size, char ***rfile)
{
	char **copy;
	size_t	i;

	i = 0;
	printf("CALL for size: %ld\n", size);
	copy = (char **)malloc((size + 1) * sizeof(char *));
	if (!copy)
		return (false);
	copy[size] = NULL;
	while (*rfile[i])
	{
		copy[i] = *rfile[i];
		i++;
	}
	// print_darr(copy);
	free_dtab(*rfile);
	*rfile = copy;
	return (true);
}

static bool	extract_file(int _fd, char ***rfile)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 1;
	*rfile = (char **)malloc((size + 1) * sizeof(char *));
	if (!*rfile)
		return (false);
	*rfile[size] = NULL;
	*rfile[i] = get_next_line(_fd);
	if (errno)
		return (free_dtab(*rfile), false);
	while (*rfile[i])
	{
		size++;
		if (!resize_arr(size, rfile))
			return (free_dtab(*rfile), false);
		// *rfile[size] = NULL;
		i++;
		*rfile[i] = get_next_line(_fd);
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
		return (print_error(EINVAL, "could not open file"), false);
	if (!extract_file(fd, rfile))
		return (print_error(errno, "during file extraction"), false);
	return (true);
}

bool	fetch_map(char *arg, t_map *_map)
{
	char **rfile;
	
	(void)_map;
	rfile = NULL;
	if (!arg)
		return (print_error(EINVAL, "expected file, got NULL pointer"), false);
	if (!ext_is_valid(arg))
		return (print_error(EINVAL, "extension should be .cub"), false);
	if (!open_file(arg, &rfile))
		return (false);
	free_dtab(rfile);
	return(true);
}
