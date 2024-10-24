//HEADER

#include "cub3D.h"

static int	check_collisions(double x, double y, t_ray *r)
{
	ssize_t	i;
	ssize_t	j;

	i = (ssize_t)y;
	j = (ssize_t)x;
	if (i < 0 || j < 0 || i > r->map.msize.i || j > r->map.msize.j \
		|| !r->map.map[i][j])
		return (-1);
	if (r->map.map[i][j] == '1')
		return (1);
	return (0);
}

int	find_wall(t_ray *r, t_point *pt, t_point *step)
{
	int	i;

	i = check_collisions(pt->x, pt->y, r);
	while (!i)
	{
		pt->x += step->x;
		pt->y += step->y;
		i = check_collisions(pt->x, pt->y, r);
	}
	return (i);
}

void	vertical_hitpt(t_ray *r)
{
	r->i = fmod(r->vhitpt.y, 1.0);
	if (r->r_angle > 90.0 && r->r_angle < 270.0)
	{
		r->i = 1.0 - r->i;
		r->cwall = r->map.we;
	}
	else
		r->cwall = r->map.ea;
}
