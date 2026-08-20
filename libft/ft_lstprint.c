/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:39:50 by dstumpf           #+#    #+#             */
/*   Updated: 2026/07/13 10:52:03 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst, void (*print_fn)(void *content))
{
	t_node	*cursor;

	if (!lst)
		return ;
	cursor = lst->head;
	while (cursor)
	{
		print_fn(cursor->content);
		cursor = cursor->next;
	}
}
