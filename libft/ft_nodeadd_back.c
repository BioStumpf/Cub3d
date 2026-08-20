/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:45:32 by dstumpf           #+#    #+#             */
/*   Updated: 2026/05/08 08:44:12 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_nodeadd_back(t_node **lst, t_node *new, t_node *tail)
{
	t_node	*last_node;

	if (!lst || !new)
		return (NULL);
	last_node = ft_nodelast(*lst);
	if (!last_node)
	{
		*lst = new;
		return (new);
	}
	last_node->next = new;
	return (tail);
}
