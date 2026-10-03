/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 10:51:43 by dstumpf           #+#    #+#             */
/*   Updated: 2026/10/03 10:56:16 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data.h"

int	focus_out(void *param)
{
	ft_bzero(&((t_game *)param)->keys, sizeof(t_keys));
	return (0);
}
