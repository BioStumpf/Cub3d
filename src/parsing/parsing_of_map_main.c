/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_of_map_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nilsdruon <nilsdruon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 16:24:42 by nildruon          #+#    #+#             */
/*   Updated: 2026/11/11 02:44:45 by nilsdruon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <errno.h>
#include <string.h>

static char	*add_right_padding(char	*line, t_game	*game)
{
	char	*trimmed;
	char	*ret;

	trimmed = ft_strtrim(line, "\n");
	if(!trimmed)
		return(NULL);
	ret = ft_calloc(game->map.width + 1, sizeof(char));
	if(!ret)
		return(free(trimmed), NULL);
	ft_memset(ret, ' ', game->map.width);
	ft_memcpy(ret, trimmed, ft_strlen(trimmed));
	free(trimmed);
	return(ret);
}

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
		game->map.grid[i] = add_right_padding(line, game);
		free(line);
		if (!game->map.grid[i])
			return (ft_printf(2, "Error\nmalloc fail in store_map\n"), 0);
		i++;
	}
	return (1);
}

bool	get_map(char	*file, size_t map_start, t_game	*game)
{
	int	file_fd;

	if (!get_map_size(file, game, map_start))
		return (0);
	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
		return (ft_printf(2, "%s: %s\n", file, strerror(errno)), 0);
	if (!skip_all_pre_map(file_fd, map_start))
		return (close(file_fd), 0);
	if (!store_map(file_fd, game))
		return (close(file_fd), 0);
	if (!map_is_valid(game->map.grid))
		return (close(file_fd), 0);
	return (close(file_fd), 1);
}
