/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswitch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:40:58 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:40:58 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_lstswitch(t_list *lst, t_node *dst,
		t_node *src, t_node *pre_src)
{
	if (lst->len < 2 || src == dst || pre_src == dst)
		return (false);
	if (src == lst->head)
		lst->head = src->next;
	if (src == lst->tail)
		lst->tail = pre_src;
	if (pre_src)
		pre_src->next = src->next;
	if (dst == lst->tail)
		lst->tail = src;
	if (!dst)
	{
		src->next = lst->head;
		lst->head = src;
	}
	else
	{
		src->next = dst->next;
		dst->next = src;
	}
	return (true);
}
