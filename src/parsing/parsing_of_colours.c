/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_of_colours.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nilsdruon <nilsdruon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 16:20:18 by nildruon          #+#    #+#             */
/*   Updated: 2026/11/11 00:07:13 by nilsdruon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include <errno.h>

static int	get_num(char	**line, bool last_num)
{
	char	*num_s;
	int		num;
	int		i;

	i = 0;
	while (line[0][i] && ft_isdigit(line[0][i]))
		i++;
	if (i > 3 || i == 0 || (!last_num && (line[0][i] && line[0][i] != ','))
		|| (last_num && line[0][i] != '\n'))
	{
		ft_printf(2, "Error\nInvalid input for the colours, check specs\n");
		return (-42);
	}
	num_s = ft_calloc(i + 1, sizeof(char));
	if (!num_s)
		return (ft_printf(2, "Error\nCalloc failed in get_num"), -42);
	ft_strlcpy(num_s, line[0], i +1);
	num = ft_atoi(num_s);
	if (!last_num)
		*line += i +1;
	else
		*line += i;
	free(num_s);
	return (num);
}

//Ai explenation on how a rgb is built in an int
//Bits:      31......24 | 23......16 | 15.......8 | 7........0
//Content:   [  0x00  ] | [   Red  ] | [  Green ] | [  Blue  ]

static bool	get_colours_help(char	*line, int	*to_store_in)
{
	int	col_r;
	int	col_g;
	int	col_b;

	line += 1;
	while (ft_iswhitespace(*line))
		line += 1;
	col_r = get_num(&line, 0);
	if (col_r < 0 || col_r > 255)
		return (0);
	col_g = get_num(&line, 0);
	if (col_g < 0 || col_g > 255)
		return (0);
	col_b = get_num(&line, 1);
	if (col_b < 0 || col_b > 255)
		return (0);
	if (col_r == -1 || col_g == -1 || col_b == -1)
		return (0);
	*to_store_in = col_r << 16 | col_g << 8 | col_b;
	return (1);
}

bool	get_colours(char	*line, t_game *game)
{
	bool	ret;

	ret = 0;
	if (ft_strncmp(line, "F", 1) == 0)
		ret = get_colours_help(line, &game->floor);
	if (ft_strncmp(line, "C", 1) == 0)
		ret = get_colours_help(line, &game->ceiling);
	return (ret);
}
