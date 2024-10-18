/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_darr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:07:34 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/17 15:06:08 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	print_darr(char **arr, bool verbose)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!arr || !(*arr))
	{
		printf("adress: %p\n", arr);
		return;
	}	
	if (verbose)
	{
		printf("arr adress:		%p\n", arr);
		printf("  |");
		while (j <= ft_strlen(arr[i]))
			printf(" %ld |", j++);
		printf("\n");
		
	}
	while (arr[i])
	{
		j = 0;
		if (verbose)
		{
			printf("%ld |", i);
			while (arr[i][j])
				printf(" %c |", arr[i][j++]);
			printf("\n");
		}
		else
			printf("%s\n", arr[i]);
		i++;
	}
}
