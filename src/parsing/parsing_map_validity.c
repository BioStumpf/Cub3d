/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_validity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 16:49:06 by nildruon          #+#    #+#             */
/*   Updated: 2026/10/09 16:51:42 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static bool	is_valid_surr_char(char c)
{
	if (is_player(c) || c == '1' || c == '0')
		return (1);
	return (0);
}

static bool	are_surrondings_valid(char	**map, size_t pos_y, size_t pos_x)
{
	char	curr_c;
	size_t	valid_cnt;

	curr_c = map[pos_y][pos_x];
	if (curr_c == '1' || curr_c == ' ')
		return (1);
	if ((curr_c == '0' || is_player(curr_c)) && (pos_y == 0 || pos_x == 0))
		return (0);
	valid_cnt = 0;
	if (is_valid_surr_char(map[pos_y -1][pos_x]))
		valid_cnt++;
	if (map[pos_y +1] && is_valid_surr_char(map[pos_y +1][pos_x]))
		valid_cnt++;
	if (is_valid_surr_char(map[pos_y][pos_x -1]))
		valid_cnt++;
	if (map[pos_y][pos_x +1] && is_valid_surr_char(map[pos_y][pos_x +1]))
		valid_cnt++;
	if (valid_cnt == 4)
		return (1);
	return (0);
}

bool	map_is_valid(char	**map)
{
	size_t	player_cnt;
	size_t	i;
	size_t	j;

	i = 0;
	player_cnt = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
				player_cnt++;
			if (player_cnt > 1)
				return (ft_printf(2, "Error\nToo players in the map\n"), 0);
			if (!are_surrondings_valid(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	if (player_cnt == 0)
		return (ft_printf(2, "Error\nNo player placed in the map\n"), 0);
	return (1);
}
