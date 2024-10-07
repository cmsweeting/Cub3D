/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_darr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:07:34 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/07 14:41:09 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	print_darr(char **arr, bool verbose)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		if (verbose)
			printf("arr[%ld]: %s\n", i, arr[i]);
		else
			printf("%s\n", arr[i]);
		i++;
	}
}