/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterative_floodfill.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:39:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/14 17:07:52 by cdomet-d         ###   ########.fr       */
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
	bool	*visited;
	t_co	cur;

	q = (t_queue){0};
	q.item = malloc(((map.msize.i * map.msize.j) * 2) * sizeof(t_co));
	if (!q.item)
		return (false);
	visited = malloc(((map.msize.i * map.msize.j)) * sizeof(bool));
	if (!visited)
		return (false);
	for (size_t i = 0; i < map.msize.i * map.msize.j; i++)
		visited[i] = false;
	push(&q, (t_co){map.p.i, map.p.j});
	while (q.frt < q.end)
	{
		cur = q.item[q.frt++];
		if (map.map[cur.i][cur.j] != '0')
			continue;
		if ((cur.i == 0 || cur.i == map.msize.i -1 || \
		cur.j == 0 || cur.j == map.msize.j - 1) && \
		map.map[cur.i][cur.j] == '0')
			return (false);
		map.map[cur.i][cur.j] = ' ';
		visited[cur.i * map.msize.j + cur.j] = true;
		if (map.map[cur.i + 1][cur.j] == '0' && !visited[cur.i + 1 * map.msize.j + cur.j])
			push(&q, (t_co){cur.i + 1, cur.j});
		if (map.map[cur.i - 1][cur.j] == '0' && !visited[cur.i - 1 * map.msize.j + cur.j])
			push(&q, (t_co){cur.i - 1, cur.j});
		if (map.map[cur.i][cur.j + 1] == '0' && !visited[cur.i * map.msize.j + cur.j + 1])
			push(&q, (t_co){cur.i, cur.j + 1});
		if (map.map[cur.i][cur.j - 1] == '0'&& !visited[cur.i * map.msize.j + cur.j - 1])
			push(&q, (t_co){cur.i, cur.j - 1});
	}
	printf("sizeof: %ld\n%ld || %ld\n", map.msize.i * map.msize.j * 2, q.frt, q.end);
	free(q.item);
	free(visited);
	return (true);
}

