/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_strcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:49:09 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/28 09:47:32 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	pstart(t_card pcard, t_co p)
{
	if (p.i == 0 && p.j == 0)
	{
		printf("\nPlayer position not found\n");
		return;
	}
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

static void	pimg(t_img	texture)
{
	printf("Img\n---\n");
	printf("ptr		: %p\n", texture.ptr);
	printf("xpm_data	: %s\n", texture.sxpm);
	printf("bpp		: %d\n", texture.bpp);
	printf("xpms		: %d\n", texture.bpp);
	printf("len		: %d\n", texture.len);
	printf("endian		: %d\n", texture.endian);
	printf("---\n");
}

void	print_parser(t_parser parse)
{
	pstart(parse.pcard, parse.p);
	printf("\n");
	printf("east: %s\n", parse.ea.pto_file);
	printf("west: %s\n", parse.we.pto_file);
	printf("north: %s\n", parse.no.pto_file);
	printf("south: %s\n", parse.so.pto_file);
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
	printf("MHeight: %ld || MWidth %ld\n", ray.map.msize.i, ray.map.msize.j);
	pimg(ray.map.ea);
	pimg(ray.map.we);
	pimg(ray.map.so);
	pimg(ray.map.no);
}
