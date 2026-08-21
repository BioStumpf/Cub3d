/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 11:21:52 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/21 14:34:53 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "rendering.h"
#include <mlx.h>

static bool	init_img(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
		return (false);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits,
		&game->img.len, &game->img.end);
	game->img.bytes = game->img.bits / 8;
	return (true);
}

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		cleanup(game, PRINT, ERR);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3d");
	if (!game->win)
		cleanup(game, PRINT, ERR);
	if (!init_img(game))
		cleanup(game, PRINT, ERR);
}

void	game_loop(t_game *game)
{
	setup_player(game);
	// print_player(game);
	init_mlx(game);
	init_hooks(game);
	mlx_loop(game->mlx);
}
