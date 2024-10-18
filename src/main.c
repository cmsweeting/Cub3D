/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:17:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/18 11:21:59 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	fill_rdata(t_ray *rdata, t_parser fdata)
{
	size_t	i;

	i = -1;
	rdata->map = fdata;
	if (init_display(rdata, fdata))
		return (false);
	rdata->map.map = fdata.map;
	rdata->map.msize.i = fdata.msize.i - 1;
	rdata->map.msize.j = fdata.msize.j - 1;
	return (true);
}

int	main(int ac, char *av[])
{
	t_parser	fdata;
	t_ray		rdata;

	if (ac != 2)
		return (perr(EINVAL, "expected one argument"), EINVAL);
	fdata = (t_parser){0};
	rdata = (t_ray){0};
	if (!fill_fdata(av[1], &fdata))
		return (free_fdata(&fdata), EINVAL);
	if (!fdata_is_valid(&fdata))
		return (free_fdata(&fdata), EINVAL);
	if (!fill_rdata(&rdata, fdata))
		return (dall(&fdata, &rdata), perr(EINVAL, "invalid texture"), EINVAL);
	run_game(&rdata);
	dall(&fdata, &rdata);
}
