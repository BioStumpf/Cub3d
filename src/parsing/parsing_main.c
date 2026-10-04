/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 14:23:01 by nildruon          #+#    #+#             */
/*   Updated: 2026/10/04 16:56:04 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <string.h>
#include <errno.h>

/*static bool get_colours(int fd, t_game *game)
{
	
}*/

static bool find_texture_path(char	*line, char	**cardinal_dir, int curr_pos)
{
	if (curr_pos == 0 && strncmp(line, "NO ", 3) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	if (curr_pos == 1 && strncmp(line, "SO ", 3) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	if (curr_pos == 2 && strncmp(line, "WE ", 3) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	if (curr_pos == 3 && strncmp(line, "EA ", 3) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	line +=3;
	*cardinal_dir = ft_strtrim(line, "\n");
	if(!*cardinal_dir)
		return(ft_printf(2, "Error\ntrim failed in find_texture_path"), NULL);
	return (1);
}

static bool get_textures(int fd, t_game *game)
{
	char	*curr;
	bool	ret;
	int		i;

	i = 0;
	while (i < 4)
	{
		curr = get_next_line(fd);
		if(!curr)
			return(0);
		if(i == 0)
			ret = find_texture_path(curr, &game->no, i);
		if(i == 1)
			ret = find_texture_path(curr, &game->so, i);
		if(i == 2)
			ret = find_texture_path(curr, &game->we, i);
		if(i == 3)
			ret = find_texture_path(curr, &game->ea, i);
		if(!ret)
			return(0);
		i++;
		free(curr);
	}
	return(1);
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
	int file_fd;
	(void)game;

	if (!check_filename_format(file))
		return (0);
	file_fd = open(file, O_RDONLY);
	if(file_fd == -1)
		return (ft_printf(2, "%s: %s\n", file, strerror(errno)), 0);
	if(!get_textures(file_fd, game))
		return(0);
	return (1);
}
