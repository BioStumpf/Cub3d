/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm_mid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:40:41 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 18:40:41 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstmid_rm(t_list *lst, t_node *to_rm,
		t_node *prev, void (*del)(void *))
{
	if (lst->len == 0)
		return ;
	if (to_rm == lst->head)
		lst->head = to_rm->next;
	if (to_rm == lst->tail)
		lst->tail = prev;
	if (prev)
		prev->next = to_rm->next;
	ft_lstdelone(to_rm, del);
	lst->len--;
}
