/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_of_colours.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 16:20:18 by nildruon          #+#    #+#             */
/*   Updated: 2026/10/09 16:54:30 by nildruon         ###   ########.fr       */
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
		return (-42);
	num_s = ft_calloc(i + 1, sizeof(char));
	if (!num_s)
		return (ft_printf(2, "Error\nCalloc failed in get_num"), 0);
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

static bool	get_colours_help(char	*line, int	*to_store_in, char surface)
{
	int	col_r;
	int	col_g;
	int	col_b;

	if (surface == 'F' && ft_strncmp(line, "F ", 2) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	if (surface == 'C' && ft_strncmp(line, "C ", 2) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	line += 2;
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
	if (line[0] != '\n')
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	*to_store_in = col_r << 16 | col_g << 8 | col_b;
	return (1);
}

bool	get_colours(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	if (errno != 0)
	{
		ft_printf(2, "Error\ngnl fail in get_colours\n");
		return (0);
	}
	if (!line)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	if (!line)
		return (0);
	if (!get_colours_help(line, &game->floor, 'F'))
		return (free(line), 0);
	free(line);
	line = get_next_line(fd);
	if (!line)
		return (0);
	if (!get_colours_help(line, &game->ceiling, 'C'))
		return (free(line), 0);
	return (free(line), 1);
}
