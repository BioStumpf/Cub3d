/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_of_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 16:14:01 by nildruon          #+#    #+#             */
/*   Updated: 2026/10/09 17:41:23 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	find_texture_path(char	*line, char	**cardinal_dir, int curr_pos)
{
	if (curr_pos == 0 && ft_strncmp(line, "NO ", 3) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	if (curr_pos == 1 && ft_strncmp(line, "SO ", 3) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	if (curr_pos == 2 && ft_strncmp(line, "WE ", 3) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	if (curr_pos == 3 && ft_strncmp(line, "EA ", 3) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	line += 3;
	*cardinal_dir = ft_strtrim(line, "\n");
	if (!*cardinal_dir)
		return (ft_printf(2, "Error\ntrim failed in find_texture_path"), NULL);
	return (1);
}

bool	get_textures(int fd, t_game *game)
{
	char	*curr;
	bool	ret;
	int		i;

	i = 0;
	while (i < 4)
	{
		curr = get_next_line(fd);
		if (!curr)
			return (free(game->no), free(game->so), free(game->we), free(game->ea), 0);
		if (i == 0)
			ret = find_texture_path(curr, &game->no, i);
		if (i == 1)
			ret = find_texture_path(curr, &game->so, i);
		if (i == 2)
			ret = find_texture_path(curr, &game->we, i);
		if (i == 3)
			ret = find_texture_path(curr, &game->ea, i);
		free(curr);
		if (!ret)
			return (free(game->no), free(game->so), free(game->we), free(game->ea), 0);
		i++;
	}
	return (1);
}
