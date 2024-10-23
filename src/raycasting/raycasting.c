/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:29:50 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/22 18:22:03 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	vertical_intersection(t_ray *r)
{
	t_point	step;

	if (cos(radian(r->r_angle)) == 0)
		return (-1);
	step.x = 1;
	step.y = tan(radian(r->r_angle)) * 1;
	r->vhitpt.x = (int)(r->p.x);
	if (r->r_angle > 90.0 && r->r_angle < 270.0)
	{
		step.x *= -1;
		r->vhitpt.x -= EP;
	}
	else
	{
		step.y *= -1;
		r->vhitpt.x += 1;
	}
	r->vhitpt.y = r->p.y + tan(radian(r->r_angle)) * (r->p.x - r->vhitpt.x);
	if (find_wall(r, &r->vhitpt, &step) == -1)
		return (-1);
	return (get_distance(&r->vhitpt, r));
}

static double	horizontal_intersection(t_ray *r)
{
	t_point	step;

	if (sin(radian(r->r_angle)) == 0)
		return (-1);
	step.y = 1;
	step.x = 0;
	if (cos(radian(r->r_angle)) != 0)
		step.x = 1 / tan(radian(r->r_angle));
	r->hhitpt.y = (int)(r->p.y);
	if (r->r_angle > 0.0 && r->r_angle < 180.0)
	{
		step.y *= -1;
		r->hhitpt.y -= EP;
	}
	else
	{
		step.x *= -1;
		r->hhitpt.y += 1;
	}
	r->hhitpt.x = r->p.x;
	if (cos(radian(r->r_angle)) != 0)
		r->hhitpt.x = r->p.x + (r->p.y - r->hhitpt.y) / tan(radian(r->r_angle));
	if (find_wall(r, &r->hhitpt, &step) == -1)
		return (-1);
	return (get_distance(&r->hhitpt, r));
}

static double	smallest_distance(double hor, double ver, t_ray *r)
{
	double	smallest;

	smallest = 1.0;
	if (ver == -1 || (hor < ver && hor > 0))
	{
		smallest = hor;
		r->i = fmod(r->hhitpt.x, 1.0);
		if (r->r_angle > 0.0 && r->r_angle < 180.0)
			r->cwall = r->map.no;
		else
		{
			r->i = 1.0 - r->i;
			r->cwall = r->map.so;
		}
		return (smallest);
	}
	else if (ver > 0)
	{
		smallest = ver;
		vertical_hitpt(r);
	}
	return (smallest);
}

static void	fish_eye(double *distance, int i, t_ray *r)
{
	double	angle;

	angle = (i - r->hs_width) * r->rayspacing;
	*distance *= cos(radian(angle));
}

int	raycasting(t_ray *r)
{
	int		i;
	double	horizontal;
	double	vertical;
	double	distance;

	i = 0;
	move(r);
	// on ajoute 30° à l'angle central (c_angle) pour obtenir l'angle du rayon le plus à gauche du plan de projection
	// car on dessine de gauche à droite / on remplie l'image de gauche à droite
	// 30 = moitié de FOV
	// c_angle est l'angle du rayon au centre du FOV donc il y a 30 degres de chaque coté de ce rayon
	r->r_angle = r->c_angle + 30.0f;
	// si l'angle dépasse 360° ou devient < 0° on le normalise pour le remettre dans l'interval [0,360]
	normalise_angle(&r->r_angle);
	// on va boucler S_WIDTH qui est le nombre de colonne de pixel à dessiner dans img
	// c'est aussi le nombre de rayon
	while (i < S_WIDTH)
	{
		// horizontal est la distance entre le joueur et la première intersection avec un mur horizontal
		// c'est aussi la longueur du rayon projeté vers un mur horizontal
		horizontal = horizontal_intersection(r);
		// pareil mais avec un mur vertical
		vertical = vertical_intersection(r);
		// distance est la distance la plus petite entre horizontal et vertical
		distance = smallest_distance(horizontal, vertical, r);
		// permet d'avoir des murs droit et pas courbés
		fish_eye(&distance, i, r);
		// ici on va dessiner la colonne de pixel
		draw_column(r, distance, i);
		// on augmente l'angle pour passer au rayon suivant / à la colonne de pixel suivante
		r->r_angle -= r->rayspacing;
		normalise_angle(&r->r_angle);
		i++;
	}
	mlx_put_image_to_window(r->mlx, r->win, r->img.ptr, 0, 0);
	mlx_put_image_to_window(r->mlx, r->win, r->minim.ptr, 5, 5);
	return (0);
}
