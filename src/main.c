/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 09:48:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/10/09 18:02:53 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "libft.h"
#include "rendering.h"
#include "parsing.h"

// print_map(&game); -> after dummy_map or when nils
// generated the map this is how it can be printed

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
		return (1);
	//dummy_map(&game); 
	game_loop(&game);
	print_map(&game);
	cleanup(&game, NOPRINT, OK);
}
