/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:17:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/19 21:48:19 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char *av[])
{
	t_ray		r;

	if (ac != 2)
		return (perr(EINVAL, "expected one argument"), EINVAL);
	r = (t_ray){0};
	if (!fill_f(av[1], &r.map))
		return (free_f(&r.map), EINVAL);
	if (!f_is_valid(&r.map))
		return (free_f(&r.map), EINVAL);
	if (init_display(&r))
		return (dall(&r), perr(EINVAL, "invalid texture"), EINVAL);
	run_game(&r);
	dall(&r);
}
