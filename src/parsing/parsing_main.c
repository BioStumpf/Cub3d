/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nilsdruon <nilsdruon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 14:23:01 by nildruon          #+#    #+#             */
/*   Updated: 2026/11/10 23:33:35 by nilsdruon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <string.h>
#include <errno.h>

static bool	check_filename_format(char	*file)
{
	size_t	f_name_size;

	f_name_size = ft_strlen(file);
	if (f_name_size < 5)
	{
		ft_putendl_fd("Error: filename too short\nusage: filename.cub", 2);
		return (0);
	}
	if (ft_strncmp(&file[f_name_size - 4], ".cub", 4) != 0)
	{
		ft_putendl_fd("Error: Filename doenst end with .cub", 2);
		ft_putendl_fd("usage: filename.cub", 2);
		return (0);
	}
	return (1);
}

static bool	if_map_started(char	*line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (0);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static bool	check_which_elem_and_store(char	*line, t_game	*game,
		size_t *elem_cnt)
{
	if (!line)
		return (0);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		return ((*elem_cnt)++, get_textures(line, game));
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return ((*elem_cnt)++, get_colours(line, game));
	else if (is_delim_valid(line))
		return (1);
	else
		return (0);
}

static bool	parse_data_help(int file_fd, t_game	*game,
		size_t	*map_start, size_t *elem_cnt)
{
	int		gnl_ret;
	char	*line;

	line = NULL;
	while (*map_start >= 0)
	{
		gnl_ret = get_next_line_wrapper(file_fd, &line, "parse_data_help");
		if (gnl_ret < 1)
			return (0);
		if (if_map_started(line))
			break ;
		if (!check_which_elem_and_store(line, game, elem_cnt))
			return (free(line), 0);
		free(line);
		(*map_start)++;
	}
	free(line);
	return (1);
}

bool	parse_data(char	*file, t_game *game)
{
	int		file_fd;
	size_t	map_start;
	size_t	elem_cnt;

	elem_cnt = 0;
	map_start = 0;
	if (!check_filename_format(file))
		return (0);
	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
		return (ft_printf(2, "%s: %s\n", file, strerror(errno)), 0);
	map_start = 0;
	if (!parse_data_help(file_fd, game, &map_start, &elem_cnt))
		return (close(file_fd), 0);
	if (elem_cnt != 6)
	{
		ft_printf(2, "Error\nSome Data Missing in at top of input file\n");
		return (0);
	}
	if (!get_map(file, map_start, game))
		return (close(file_fd), 0);
	close(file_fd);
	return (1);
}
