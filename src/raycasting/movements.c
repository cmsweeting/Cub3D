/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:16:41 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/21 17:50:18 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	new_position(t_ray *r, double angle)
{
	double	x;
	double	y;

	// les steps
	x = cos(radian(angle)) * 0.125;
	y = sin(radian(angle)) * 0.125;
	// on multiplie y par -1 parce que selon l'angle sin et cos sont negatif et positif et je te ferais un schema
	y *= -1.0;
	// on utilise x et y comme temp pour verifier si la nouvelle position est valable pour savoir si on peut changer les vrai varaibles p.x et p.y
	x += r->p.x;
	y += r->p.y;
	// on verifie que ça sort pas de la map et que c'est pas un mur
	if (((ssize_t)x >= 0 || (ssize_t)x <= r->map.msize.j) \
		&& ((ssize_t)y >= 0 || (ssize_t)y <= r->map.msize.i) \
		&& r->map.map[(ssize_t)y][(ssize_t)x] != '1')
	{
		r->p.x = x;
		r->p.y = y;
	}
}

static void	move_angle(t_ray *r, double *angle)
{
	// pour cette partie je te ferais un schema
	*angle = r->c_angle;
	if (r->moves.down)
		*angle += 180;
	if (r->moves.left)
	{
		if (r->moves.down)
			*angle -= 45;
		else if (r->moves.up)
			*angle += 45;
		else
			*angle += 90;
	}
	if (r->moves.right)
	{
		if (r->moves.down)
			*angle += 45;
		else if (r->moves.up)
			*angle -= 45;
		else
			*angle -= 90;
	}
	normalise_angle(angle);
}

void	move(t_ray *r)
{
	double	angle;

	// si on tourne la camera vers la gauche on augmente l'angle du rayon qui part du joueur
	// car les angles augmentent de la gauche vers la droite
	if (r->moves.lturn)
		r->c_angle += 1.0;
	// ici c'est l'inverse
	if (r->moves.rturn)
		r->c_angle -= 1.0;
	normalise_angle(&r->c_angle);
	move_angle(r, &angle);
	// si les case w et s on ete appuyées en meme temps le perso devrait pas bouger donc on change pas sa position
	// pareil pour les touches a et d
	if ((r->moves.down && r->moves.up) || (r->moves.right && r->moves.left))
		return ;
	//sinon si l'une des 4 touches a ete touchee on change la position du player
	else if (r->moves.down || r->moves.up || r->moves.right || r->moves.left)
		new_position(r, angle);
}
