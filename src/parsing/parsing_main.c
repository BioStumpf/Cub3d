/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 14:23:01 by nildruon          #+#    #+#             */
/*   Updated: 2026/10/09 17:00:02 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <string.h>
#include <errno.h>

static bool	is_delim_valid(int fd)
{
	char	*line;
	size_t	line_len;

	line = get_next_line(fd);
	if (!line)
		return (0);
	line_len = ft_strlen(line);
	if (!(line_len == 1 && line[0] == '\n'))
		return (free(line), 0);
	return (free(line), 1);
}

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

bool	parse_data(char	*file, t_game *game)
{
	int	file_fd;

	if (!check_filename_format(file))
		return (0);
	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
		return (ft_printf(2, "%s: %s\n", file, strerror(errno)), 0);
	if (!get_textures(file_fd, game))
		return (0);
	if (!is_delim_valid(file_fd))
		return (0);
	if (!get_colours(file_fd, game))
		return (0);
	if (!is_delim_valid(file_fd))
		return (0);
	if (!get_map(file, file_fd, game))
		return (0);
	return (1);
}
