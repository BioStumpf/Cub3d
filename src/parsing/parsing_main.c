/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nilsdruon <nilsdruon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 14:23:01 by nildruon          #+#    #+#             */
/*   Updated: 2026/10/07 12:55:53 by nilsdruon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <string.h>
#include <errno.h>

static int get_num(char	**line, bool last_num)
{
	char	*num_s;
	int		num;
	int		i;

	i = 0;
	while (line[0][i] && ft_isdigit(line[0][i]))
		i++;	
	if (i > 3 || i==0 || (!last_num && (line[0][i] && line[0][i] != ','))
		|| (last_num && line[0][i] != '\n'))
		return (-42);
	num_s = ft_calloc(i + 1, sizeof(char));
	if (!num_s)
		return (ft_printf(2, "Error\nCalloc failed in get_num"), 0);
	ft_strlcpy(num_s, line[0], i +1);
	num = ft_atoi(num_s);
	if(!last_num)
		*line += i+1;
	else
		*line += i;
	free(num_s);
	return(num);
}

//Ai explenation on how a rgb is built in an int
//Bits:      31......24 | 23......16 | 15.......8 | 7........0
//Content:   [  0x00  ] | [   Red  ] | [  Green ] | [  Blue  ]

static bool get_colours_help(char	*line, int	*to_store_in, char	surface)
{
	int	col_r;
	int	col_g;
	int	col_b;

	if (surface == 'F' && strncmp(line, "F ", 2) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	if (surface == 'C' && strncmp(line, "C ", 2) != 0)
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	line +=2;
	col_r = get_num(&line, 0);
	if(col_r < 0 || col_r > 255)
		return(0);
	col_g = get_num(&line, 0);
	if(col_g < 0 || col_g > 255)
		return(0);
	col_b = get_num(&line, 1);
	if(col_b < 0 || col_b > 255)
		return(0);
	if(col_r == -1 || col_g == -1 || col_b == -1)
		return (0);
	if(line[0] != '\n')
		return (ft_printf(2, "Error\n.cub input invalid, check README"), 0);
	*to_store_in = col_r << 16 | col_g << 8 | col_b;
	return(1);
}

static bool get_colours(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	if(!line)
		return (0);
	if(!get_colours_help(line, &game->floor, 'F'))
		return (free(line), 0);
	free(line);
	line = get_next_line(fd);
	if(!line)
		return (0);
	if(!get_colours_help(line, &game->ceiling, 'C'))
		return (free(line), 0);
	return(1);
}

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

static bool	is_delim_valid(int fd)
{
	char	*line;
	size_t	line_len;
	
	line = get_next_line(fd);
	if(!line)
		return(0);
	line_len = ft_strlen(line);
	if(!(line_len == 1 && line[0] == '\n'))
		return(0);
	return (1);
}

static int get_map_size_help(int file_fd, int	*cnt, t_game	*game)
{
	char	*line;
	size_t	line_len;

	if (game->map.height == 2147483647)
			return (ft_printf(2, "Error\nToo big map, be reasonable!\n"), 0);
	line = get_next_line(file_fd);
	if (errno != 0)
	{
		ft_printf(2, "Error\ngnl fail in get_map_size\n");
		return(close(file_fd), -1);
	}
	if (!line)
		return (0);
	line_len = ft_strlen(line);
	if(line[line_len -1] == '\n')
		line_len--;
	if(line_len > 2147483647)
		return (ft_printf(2, "Error\nToo big map, be reasonable!\n"), 0);
	if (*cnt > 7)
	{
		if ((int)line_len > game->map.width)
			game->map.width = line_len;
		game->map.height++;
	}
	return ((*cnt)++, free(line), 1);
}

static bool get_map_size(char	*file, t_game	*game)
{
	int		file_fd;
	int		cnt;
	int		help_ret;

	file_fd = open(file, O_RDONLY);
	if(file_fd == -1)
		return (ft_printf(2, "%s: %s\n", file, strerror(errno)), 0);
	cnt = 0;
	while (1)
	{
		help_ret = get_map_size_help(file_fd, &cnt, game);
		if(help_ret == -1)
			return(0);
		if(help_ret == 0)
			break ;
	}
	if (game->map.height < 3 || game->map.width < 3)
		return (close(file_fd), 0);
	return (close(file_fd), 1);
}

static bool store_map(int fd, t_game	*game)
{
	size_t	i;
	char	*line;

	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char	*));
	if(!game->map.grid)
		return(ft_printf(2, "Error\nmalloc fail in store_map\n"), 0);
	i = 0;
	while ((int)i < game->map.height)
	{
		line = get_next_line(fd);
		if (errno != 0)
		{
			ft_printf(2, "Error\ngnl fail in store_map\n");
			return(close(fd), 0);
		}
		if (!line)
			break ;
		game->map.grid[i] = ft_strtrim(line, "\n");
		free(line);
		if(!game->map.grid[i])
			return(ft_printf(2, "Error\nmalloc fail in store_map\n"), 0);
		i++;
	}
	return (1);
}

static bool is_player(char c)
{
	if(c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static bool is_valid_surr_char(char	c)
{
	if(is_player(c) || c == '1' || c == '0')
		return (1);
	return (0);
}

static bool are_surrondings_valid(char	**map, size_t pos_y, size_t pos_x)
{
	char curr_c;
	size_t valid_cnt;

	curr_c = map[pos_y][pos_x];
	if(curr_c == '1' || curr_c == ' ')
		return (1);
	if((curr_c == '0' || is_player(curr_c)) && (pos_y == 0 || pos_x == 0))
		return(0);
	valid_cnt = 0;
	if (is_valid_surr_char(map[pos_y -1][pos_x]))
		valid_cnt++;
	if (map[pos_y +1] && is_valid_surr_char(map[pos_y +1][pos_x]))
		valid_cnt++;
	if (is_valid_surr_char(map[pos_y][pos_x -1]))
		valid_cnt++;
	if (map[pos_y][pos_x +1] && is_valid_surr_char(map[pos_y][pos_x +1]))
		valid_cnt++;
	if(valid_cnt == 4)
		return (1);
	return (0);
}

static bool map_is_valid(char	**map)
{
	size_t	player_cnt;
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	player_cnt = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (is_player(map[i][j]))
				player_cnt++;
			if(player_cnt > 1)
				return(0);
			if (!are_surrondings_valid(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static bool get_map(char	*file, int already_open_fd, t_game	*game)
{
	if(!get_map_size(file, game))
		return(0);
	if(!store_map(already_open_fd, game))
		return(0);
	if(!map_is_valid(game->map.grid))
		return(0);
	return(1);
}

bool	parse_data(char	*file, t_game *game)
{
	int file_fd;

	if (!check_filename_format(file))
		return (0);
	file_fd = open(file, O_RDONLY);
	if(file_fd == -1)
		return (ft_printf(2, "%s: %s\n", file, strerror(errno)), 0);
	if(!get_textures(file_fd, game))
		return(0);
	if(!is_delim_valid(file_fd))
		return(0);
	if(!get_colours(file_fd, game))
		return(0);
	if(!is_delim_valid(file_fd))
		return(0);
	if(!get_map(file, file_fd, game))
		return(0);
	return (1);
}
