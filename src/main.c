/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nilsdruon <nilsdruon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 09:48:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/11/10 23:30:26 by nilsdruon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "libft.h"
#include "rendering.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Error: Wrong amount of arguments", 2);
		ft_putendl_fd("usage: ./cub3d file.cub", 2);
		return (0);
	}
	ft_bzero(&game, sizeof(game));
	(void)argv;
	if (!parse_data(argv[1], &game))
		return (cleanup(&game, NOPRINT, ERR), 1);
	game_loop(&game);
	cleanup(&game, NOPRINT, OK);
}
