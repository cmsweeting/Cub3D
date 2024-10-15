/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:12:53 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/15 12:34:22 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dest && !src && n != 0)
		return (dest);
	if (!n)
		return (dest);
	if (src < dest)
	{
		while (n > 0)
		{
			((t_co *)dest)[n - 1] = ((t_co *)src)[n - 1];
			n--;
		}
	}
	else
	{
		while (++i < n)
			((t_co *)dest)[i] = ((t_co *)src)[i];
	}
	return (dest);
}
