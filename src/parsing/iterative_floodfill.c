/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterative_floodfill.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:39:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/11 18:41:25 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	push(t_queue *q, t_co node)
{
	q->item[q->end] = node;
	q->end++;
}

bool	iwall(t_map map)
{
	t_queue	q;

	q = (t_queue){0};
	
	q.item = malloc((map.msize.i * map.msize.j) * sizeof(t_co));
	if (!q.item)
		return (false);
	push(&q, (t_co){map.p.i, map.p.j});
	while (q.frt < q.end)
	{
			print_darr(map.map, false);
			if (map.p.i == 0 || map.p.i == map.msize.i -1 || map.p.j == 0 || map.p.j == map.msize.j || map.map[map.p.i][map.p.j] != '0')
			{
				if (map.map[map.p.i][map.p.j] == '0')
				{
					map.map[map.p.i][map.p.j] = ' ';
					return (false);
				}
				map.map[map.p.i][map.p.j] = ' ';
				push(&q, (t_co){map.p.i + 1, map.p.j});
				push(&q, (t_co){map.p.i, map.p.j + 1});
				push(&q, (t_co){map.p.i - 1, map.p.j});
				push(&q, (t_co){map.p.i, map.p.j - 1});
			}
		q.frt++;
	}
	return (true);
}
