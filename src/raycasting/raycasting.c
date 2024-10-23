/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:29:50 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/23 18:54:07 by csweetin         ###   ########.fr       */
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

	// sin(0) = 0
	// sin(360) = 0
	// sin(180) = 0
	// si le rayon a un angle de 0, 360 ou 270 ca veut dire qu'il est parfaitement horizontal
	// donc il ne rencontrera jamais de mur horizontal donc on return -1
	if (sin(radian(r->r_angle)) == 0)
		return (-1);
	// step.y est egal a la hauteur d'un cub 
	// nos cub font 64 px mais pour les calculs on choisit une unite de 1 px pour avoir moins d'erreur d'arrondi avec les doubles
	step.y = 1;
	// si cos(angle) = 0
		// cos(90) = 0
		// cos (270) = 0
		// si l'angle de notre rayon est de 90 ou 270 ca veut dire qu'il est parfaitement vertical
		// donc quand on cherchera le mur pas besoin de modifier hhitpt.x il faudra juste augmenter ou diminer hhitpt.y donc on laisse step.x a 0
		// de plus tan(a) = sin(a) / cos(a)
		// or si cos(a) est egal a 0 on ferait une division par zero ce qui est interdit
	// sinon
		// on calcul step.x qu'on utilisera plus tard pour passer au point suivant de notre rayon et voir si c'est un mur
	step.x = 0;
	if (cos(radian(r->r_angle)) != 0)
		step.x = 1 / tan(radian(r->r_angle));
	// hhitpoint.y c'est la coordonnee y du premier point sur une grille
	// PS : a chaque fois on regarde les points sur les grilles parce qu'un mur fait une case entiere donc si on regarde sur les grilles on est sur de pas louper de mur 
	// si r->p.y = 3.5 px (qui est la ligne 3 dans le tableau map) alors r->hhitpt.y = 3 px
	r->hhitpt.y = (int)(r->p.y);
	if (r->r_angle > 0.0 && r->r_angle < 180.0)
	{
		// si le rayon est dirige vers le haut on veut que step.y soit negatif
		// vu que l'axe y augmente du haut vers le bas et la le rayon va du bas vers le haut
		// plus tard pour trouver le prochain point il faudra decrementer r->hhitpt.y
		step.y *= -1;
		// pour l'instant r->hhitpt.y est sur la case du player mais nous on veut aller voir la case au dessus du player vu que le rayon regarde vers le haut
		// donc on soustrait epsilon ce qui ferait r->hhitpt.y = 2.99999 et on irait chercher dans le tableau map la ligne 2
		r->hhitpt.y -= EP;
	}
	else
	{
		// on sait que tan(a) = sin(a) / cos(a)
		// et step.x = 1 / tan(radian(r->r_angle));
		// angle entre 180 et 270
			// le cos et le sin d'un angle entre 180 et 270 degres est negatif ce qui ferait que tan serait positif parce que : -a / -b = + c
			// et donc step.x serait positif
			// or si l'angle du rayon est entre 180 et 270 ca veut dire que le rayon se dirige vers la gauche
			// donc on veut que step.x devienne negatif pour decrementer r->hhitpt.x plus tard quand on cherche le mur
		// angle entre 270 et 360
			// le cos d'un angle de cet interval est positif et le sin est negatif ce qui fait que le tan est negatif car : -a / b = -c
			// et donc step.x serait negatif
			// or si l'angle du rayon est dans cet interval ca veut dire que le rayon se dirige vers la droite
			// donc on veut que step.x devienne positif pour incrementer r->hhitpt.x plus tard quand on cherche le mur
		step.x *= -1;
		// ici le rayon regarde vers le bas donc on ajoute 1 pour aller voir la case d'apres
		r->hhitpt.y += 1;
	}
	// meme logique que pour step.x
	r->hhitpt.x = r->p.x;
	if (cos(radian(r->r_angle)) != 0)
		r->hhitpt.x = r->p.x + (r->p.y - r->hhitpt.y) / tan(radian(r->r_angle));
	// on va chercher les coordonne de l'intersection avec un mur horizontal
	if (find_wall(r, &r->hhitpt, &step) == -1)
		return (-1);
	// on retourne la distance entre le joueur et l'intersection trouve juste avant
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

	// c'est l'angle entre le rayon traite actuellement et l'angle central
	// sa valeur varie entre -30 et 30
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
