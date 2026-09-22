/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 09:48:19 by dstumpf           #+#    #+#             */
/*   Updated: 2026/09/22 16:13:14 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "libft.h"
#include "rendering.h"

	// print_map(&game); -> after dummy_map or when nils
	// generated the map this is how it can be printed
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	(void)argv;
	ft_bzero(&game, sizeof(game));
	dummy_map(&game);
	game_loop(&game);
	cleanup(&game, NOPRINT, OK);
}
