/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nilsdruon <nilsdruon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 14:24:29 by nildruon          #+#    #+#             */
/*   Updated: 2026/11/10 23:33:30 by nilsdruon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "data.h"
# include <fcntl.h>
# include "get_next_line.h"
# include "ft_printf.h"

bool	map_is_valid(char	**map);
bool	get_map_size(char	*file, t_game	*game, size_t	map_start);
bool	get_map(char	*file, size_t map_start, t_game	*game);
bool	get_colours(char	*line, t_game *game);
bool	get_textures(char	*line, t_game	*game);
bool	parse_data(char	*file, t_game *game);
bool	skip_all_pre_map(int fd, int len);
bool	is_delim_valid(char	*line);
int		get_next_line_wrapper(int file_fd, char **save_into, char *func_call);

#endif