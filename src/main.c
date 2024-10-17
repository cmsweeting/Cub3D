/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:17:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/17 14:47:20 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	free_file_data(t_parser *map)
{
	if (map->no_texture)
		free(map->no_texture);
	if (map->so_texture)
		free(map->so_texture);
	if (map->we_texture)
		free(map->we_texture);
	if (map->ea_texture)
		free(map->ea_texture);
	free_dtab(map->map);
}

static void	init_parser(t_parser *map)
{
	size_t	i;

	map->p.i = -1;
	map->p.j = -1;
	map->found_p = false;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->allt_found = 0;
	map->map = NULL;
	i = 0;
	while (i < 3)
	{
		map->fcolor[i] = 0;
		map->ccolor[i] = 0;
		i++;
	}
}

void	print_parser(t_parser map)
{
	printf("player position : %ld || %ld\n", map.p.i, map.p.j);
	if (map.pcard == SO)
		printf("Player starts facing south\n");
	if (map.pcard == NO)
		printf("Player starts facing north\n");
	if (map.pcard == WE)
		printf("Player starts facing west\n");
	if (map.pcard == EA)
		printf("Player starts facing east\n");
	printf("\n");
	printf("%s\n", map.ea_texture);
	printf("%s\n", map.we_texture);
	printf("%s\n", map.no_texture);
	printf("%s\n", map.so_texture);
	printf("\n");
	printf("floor color:	%d	|	%d	|	%d\n", map.fcolor[0], \
	map.fcolor[1], map.fcolor[2]);
	printf("celling color:	%d	|	%d	|	%d\n", map.ccolor[0], \
	map.ccolor[1], map.ccolor[2]);
	printf("\n");
	print_darr(map.map, false);
	printf("\n");
}

int	main(int ac, char *av[])
{
	t_parser	fdata;
	t_ray		rdata;

	if (ac != 2)
		return (print_error(EINVAL, "expected one argument"), EINVAL);
	init_parser(&fdata);
	if (!fill_struct(av[1], &fdata))
		return (free_fdata(&fdata), EINVAL);
	if (!fdata_is_valid(&fdata))
		return (free_fdata(&fdata), EINVAL);
// TODO: init rdata.map based on fdata
	if (init_display(&rdata))
		return (free_fdata(&fdata), EINVAL);
	run_game(&rdata);
	free_fdata(&fdata);
}
