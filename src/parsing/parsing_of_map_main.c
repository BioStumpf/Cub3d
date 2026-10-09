/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_of_map_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 16:24:42 by nildruon          #+#    #+#             */
/*   Updated: 2026/10/09 16:48:52 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <errno.h>
#include <string.h>

static bool	store_map(int fd, t_game	*game)
{
	size_t	i;
	char	*line;

	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		return (ft_printf(2, "Error\nmalloc fail in store_map\n"), 0);
	i = 0;
	while ((int)i < game->map.height)
	{
		line = get_next_line(fd);
		if (errno != 0)
		{
			ft_printf(2, "Error\ngnl fail in store_map\n");
			return (close(fd), 0);
		}
		if (!line)
			break ;
		game->map.grid[i] = ft_strtrim(line, "\n");
		free(line);
		if (!game->map.grid[i])
			return (ft_printf(2, "Error\nmalloc fail in store_map\n"), 0);
		i++;
	}
	return (1);
}

bool	get_map(char	*file, int already_open_fd, t_game	*game)
{
	if (!get_map_size(file, game))
		return (0);
	if (!store_map(already_open_fd, game))
		return (0);
	if (!map_is_valid(game->map.grid))
		return (0);
	return (1);
}
