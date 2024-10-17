/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_strcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:49:09 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/17 15:32:06 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	pstart(t_card pcard, t_co p)
{
	if (pcard == SO)
		printf("Player starts facing south at: ");
	if (pcard == NO)
		printf("Player starts facing north at: ");
	if (pcard == WE)
		printf("Player starts facing west at: ");
	if (pcard == EA)
		printf("Player starts facing east at: ");
	printf("i: %ld || j: %ld\n", p.i, p.j);
}

// static void pimg(t_img	texture)
// {
// 	printf("Img\n---\n");
// 	printf("ptr: %p\n", texture.ptr);
// 	printf("xpm_data: %s\n", texture.xpm_data);
// 	printf("BPP: %d\n", texture.bpp);
// 	printf("len: %d\n", texture.len);
// 	printf("endian: %d\n", texture.endian);
// 	printf("---\n");
// }

void	print_parser(t_parser parse)
{
	printf("player position : %ld || %ld\n", parse.p.i, parse.p.j);
	printf("\n");
	printf("%s\n", parse.ea_texture);
	printf("%s\n", parse.we_texture);
	printf("%s\n", parse.no_texture);
	printf("%s\n", parse.so_texture);
	printf("\n");
	printf("floor color:	%d	|	%d	|	%d\n", parse.fcolor[0], \
	parse.fcolor[1], parse.fcolor[2]);
	printf("celling color:	%d	|	%d	|	%d\n", parse.ccolor[0], \
	parse.ccolor[1], parse.ccolor[2]);
	printf("\n");
	print_darr(parse.map, false);
	printf("\n");
}

void	print_ray(t_ray ray)
{
	printf("Map structure\n---\n");
	print_darr(ray.map.map, false);
	printf("---\n");
	printf("floor color:	%d	|	%d	|	%d\n", ray.map.fcolor[0], \
	ray.map.fcolor[1], ray.map.fcolor[2]);
	printf("celling color:	%d	|	%d	|	%d\n", ray.map.ccolor[0], \
	ray.map.ccolor[1], ray.map.ccolor[2]);
	pstart(ray.map.pcard, ray.map.p);
	printf("MapHeight: %ld || MapWidth %ld\n", ray.map.msize.i, ray.map.msize.j);
	// pimg(ray.map.ea);
	// pimg(ray.map.we);
	// pimg(ray.map.so);
	// pimg(ray.map.no);
}
