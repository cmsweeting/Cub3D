/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterative_floodfill.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:39:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/28 09:08:55 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_invalid_z(t_co msize, t_co cur, char **map)
{
	if ((cur.i == 0 || cur.i == msize.i -1 || cur.j == 0 || \
	cur.j == msize.j - 1) && map[cur.i][cur.j] == '0')
	{
		// map[cur.i][cur.j] = ' ';
		return (true);
	}
	return (false);
}

static void	push(t_queue *q, t_co node)
{
	q->item[q->end] = node;
	q->end++;
}

static void	add_to_queue(t_co cur, char **map, t_queue *q)
{
	if (map[cur.i + 1][cur.j] == '0')
		push(q, (t_co){cur.i + 1, cur.j});
	if (map[cur.i - 1][cur.j] == '0')
		push(q, (t_co){cur.i - 1, cur.j});
	if (map[cur.i][cur.j + 1] == '0')
		push(q, (t_co){cur.i, cur.j + 1});
	if (map[cur.i][cur.j - 1] == '0')
		push(q, (t_co){cur.i, cur.j - 1});
}

static bool	vresize(t_queue *q)
{
	t_co	*tmp;

	tmp = q->item;
	q->item = malloc((q->size * 2) * sizeof(t_co));
	if (!q->item)
		return (free(tmp), false);
	ft_memmove((t_co *)q->item, tmp, q->end);
	free(tmp);
	q->size *= 2;
	return (true);
}

bool	iwall(t_parser map)
{
	t_queue	q;
	t_co	cur;

	q = (t_queue){0};
	q.size = 4;
	q.item = malloc((q.size + 1) * sizeof(t_co));
	if (!q.item)
		return (false);
	push(&q, (t_co){map.p.i, map.p.j});
	while (q.frt < q.end)
	{
		cur = q.item[q.frt++];
		if (is_invalid_z(map.msize, cur, map.map))
			return (free(q.item), false);
		if (map.map[cur.i][cur.j] != '0')
			continue ;
		map.map[cur.i][cur.j] = ' ';
		if ((q.end + 4) >= q.size)
			if (!vresize(&q))
				return (false);
		add_to_queue(cur, map.map, &q);
	}
	return (free(q.item), true);
}
