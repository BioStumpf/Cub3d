/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_of_map_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 16:32:51 by nildruon          #+#    #+#             */
/*   Updated: 2026/10/09 16:41:41 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <errno.h>
#include "parsing.h"
#include <string.h>

static int	get_map_size_help(int file_fd, int	*cnt, t_game	*game)
{
	char	*line;
	size_t	line_len;

	if (game->map.height == 2147483647)
		return (ft_printf(2, "Error\nToo big map, be reasonable!\n"), 0);
	line = get_next_line(file_fd);
	if (errno != 0)
	{
		ft_printf(2, "Error\ngnl fail in get_map_size\n");
		return (close(file_fd), -1);
	}
	if (!line)
		return (0);
	line_len = ft_strlen(line);
	if (line[line_len -1] == '\n')
		line_len--;
	if (line_len > 2147483647)
		return (ft_printf(2, "Error\nToo big map, be reasonable!\n"), 0);
	if (*cnt > 7)
	{
		if ((int)line_len > game->map.width)
			game->map.width = line_len;
		game->map.height++;
	}
	return ((*cnt)++, free(line), 1);
}

bool	get_map_size(char	*file, t_game	*game)
{
	int		file_fd;
	int		cnt;
	int		help_ret;

	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
		return (ft_printf(2, "%s: %s\n", file, strerror(errno)), 0);
	cnt = 0;
	while (1)
	{
		help_ret = get_map_size_help(file_fd, &cnt, game);
		if (help_ret == -1)
			return (0);
		if (help_ret == 0)
			break ;
	}
	if (game->map.height < 3 || game->map.width < 3)
		return (close(file_fd), 0);
	return (close(file_fd), 1);
}
