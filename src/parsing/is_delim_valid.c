/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_delim_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nilsdruon <nilsdruon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 23:32:39 by nilsdruon         #+#    #+#             */
/*   Updated: 2026/11/10 23:37:05 by nilsdruon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_delim_valid(char	*line)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (!(line_len == 1 && line[0] == '\n'))
	{
		ft_printf(2, "Error\nLine Delim is wrong, check README specs\n");
		return (0);
	}
	return (1);
}
