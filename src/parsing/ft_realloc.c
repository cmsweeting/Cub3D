/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:07:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/08 15:40:41 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	ft_realloc(size_t size, char ***arr)
{
	char	**copy;
	size_t	i;

	i = 0;
	copy = malloc((size + 1) * sizeof(char *));
	if (!copy)
		return (false);
	copy[size] = NULL;
	while ((*arr) && (*arr)[i])
	{
		copy[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	*arr = copy;
	return (true);
}
