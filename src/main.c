/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:17:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/17 15:43:57 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"
#include "raycasting.h"
static void	fill_rdata(t_ray *rdata, t_parser fdata)
{
	size_t	i;

	i = -1;
	rdata->map.map = fdata.map;
	while (++i < 3)
	{
		rdata->map.ccolor[i] = fdata.ccolor[i];
		rdata->map.fcolor[i] = fdata.fcolor[i];
	}
	rdata->map.p.i = fdata.p.i;
	rdata->map.p.j = fdata.p.j;
	rdata->map.pcard = fdata.pcard;
	rdata->map.msize.i= fdata.msize.i - 1;
	rdata->map.msize.j= fdata.msize.j - 1;
	rdata->map.ea = mlx_xpm_file_to_image()
}



int	main(int ac, char *av[])
{
	t_parser	fdata;
	t_ray		rdata;

	if (ac != 2)
		return (print_error(EINVAL, "expected one argument"), EINVAL);
	fdata = (t_parser){0};
	rdata = (t_ray){0};
	if (!fill_fdata(av[1], &fdata))
		return (free_fdata(&fdata), EINVAL);
	if (!fdata_is_valid(&fdata))
		return (free_fdata(&fdata), EINVAL);
	fill_rdata(&rdata, fdata);
	print_ray(rdata);
// TODO: init rdata.map based on fdata
	if (init_display(&rdata))
		return (free_fdata(&fdata), EINVAL);
	run_game(&rdata);
	free_fdata(&fdata);
}
