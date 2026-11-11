/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_of_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nilsdruon <nilsdruon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 16:14:01 by nildruon          #+#    #+#             */
/*   Updated: 2026/11/11 01:38:05 by nilsdruon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	check_if_data_already_stored(t_game	*game, char	*line)
{
	if (ft_strncmp(line, "NO", 2) == 0 && game->no)
		return (ft_printf(2, "Error\n.cub input invalid, NO already stored\n"),
			0);
	if (ft_strncmp(line, "SO", 2) == 0 && game->so)
		return (ft_printf(2, "Error\n.cub input invalid, SO already stored\n"),
			0);
	if (ft_strncmp(line, "WE", 2) == 0 && game->we)
		return (ft_printf(2, "Error\n.cub input invalid, WE already stored\n"),
			0);
	if (ft_strncmp(line, "EA", 2) == 0 && game->ea)
		return (ft_printf(2, "Error\n.cub input invalid, EA already stored\n"),
			0);
	if (ft_strncmp(line, "F", 2) == 0 && game->floor)
		return (ft_printf(2, "Error\n.cub input invalid, F already stored\n"),
			0);
	if (ft_strncmp(line, "C", 2) == 0 && game->ceiling)
		return (ft_printf(2, "Error\n.cub input invalid, C already stored\n"),
			0);
	return (1);
}

bool	get_textures(char	*line, t_game	*game)
{
	char	*line_before;
	char	*trimmed;

	line_before = line;
	if (!check_if_data_already_stored(game, line))
		return (0);
	line += 2;
	while (ft_iswhitespace(*line))
		line += 1;
	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return (ft_printf(2, "Error\ntrim failed in find_texture_path\n"), 0);
	if (ft_strncmp(line_before, "NO", 2) == 0)
		game->no = trimmed;
	if (ft_strncmp(line_before, "SO", 2) == 0)
		game->so = trimmed;
	if (ft_strncmp(line_before, "WE", 2) == 0)
		game->we = trimmed;
	if (ft_strncmp(line_before, "EA", 2) == 0)
		game->ea = trimmed;
	return (1);
}
