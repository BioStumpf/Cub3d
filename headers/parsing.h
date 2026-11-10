/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 14:24:29 by nildruon          #+#    #+#             */
/*   Updated: 2026/10/09 16:50:07 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "data.h"
# include <fcntl.h>
# include "get_next_line.h"
# include "ft_printf.h"

bool map_is_valid(char	**map);
bool get_map_size(char	*file, t_game	*game);
bool get_map(char	*file, int already_open_fd, t_game	*game);
bool get_colours(int fd, t_game *game);
bool get_textures(int fd, t_game *game);
bool parse_data(char	*file, t_game *game);

#endif