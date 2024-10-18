/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:17:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/18 13:42:55 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char *av[])
{
	t_ray		rdata;

	if (ac != 2)
		return (print_error(EINVAL, "expected one argument"), EINVAL);
	rdata = (t_ray){0};
	if (!fill_fdata(av[1], &rdata.map))
		return (free_fdata(&rdata.map), EINVAL);
	if (!fdata_is_valid(&rdata.map))
		return (free_fdata(&rdata.map), EINVAL);
	if (init_display(&rdata))
		return (dall(&fdata, &rdata), perr(EINVAL, "invalid texture"), EINVAL);
	run_game(&rdata);
	dall(&fdata, &rdata);
}
