/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_wrapper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nilsdruon <nilsdruon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:32:41 by nilsdruon         #+#    #+#             */
/*   Updated: 2026/11/10 23:18:47 by nilsdruon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <errno.h>
#include <string.h>

int	get_next_line_wrapper(int file_fd, char	**save_into, char	*func_call)
{
	*save_into = get_next_line(file_fd);
	if (errno == 0)
	{
		if (*save_into)
			return (1);
		return (0);
	}
	ft_printf(2, "Error\n GNL failed in %s : ", func_call, strerror(errno));
	return (-1);
}
