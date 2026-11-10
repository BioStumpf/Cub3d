/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_of_map_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nilsdruon <nilsdruon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 17:16:53 by nilsdruon         #+#    #+#             */
/*   Updated: 2026/11/10 23:25:31 by nilsdruon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	skip_all_pre_map(int fd, int len)
{
	char	*line;
	int		ret;
	int		i;

	i = 0;
	while (i < len)
	{
		ret = get_next_line_wrapper(fd, &line, "skip_all_pre_map");
		if (ret == -1)
			return (0);
		if (!line)
			return (0);
		free(line);
		i++;
	}
	return (1);
}
