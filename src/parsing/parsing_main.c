/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 14:23:01 by nildruon          #+#    #+#             */
/*   Updated: 2026/10/02 16:01:09 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	(void)game;
	if (!check_filename_format(file))
		return (0);
	return (1);
}
