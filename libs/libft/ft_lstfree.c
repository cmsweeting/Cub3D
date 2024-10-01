/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:52:20 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/01 11:59:07 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

t_list	*ft_lstfree(t_list **lst)
{
	t_list	*temp;

	if (lst && *lst)
	{
		while ((*lst)->next)
		{
			temp = (*lst)->next;
			free((*lst)->data);
			free(*lst);
			*lst = temp;
		}
		free(*lst);
	}
	*lst = NULL;
	return (NULL);
}
