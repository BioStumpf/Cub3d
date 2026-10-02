/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 11:21:52 by dstumpf           #+#    #+#             */
/*   Updated: 2026/10/02 11:49:14 by dstumpf          ###   ########.fr       */
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

static void	init_tex(t_game *game, t_tex *tex, char *path)
{
	tex->img.img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img.img)
		return ;
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits,
			&tex->img.len, &tex->img.end);
	tex->img.bytes = tex->img.bits / 8;
}

static bool	init_textures(t_game *game)
{
	if (!game->no)
		return (false);
	init_tex(game, &game->no_tex, game->no);
	init_tex(game, &game->so_tex, game->so);
	init_tex(game, &game->we_tex, game->we);
	init_tex(game, &game->ea_tex, game->ea);
	if (!game->no_tex.img.img || !game->so_tex.img.img
		|| !game->we_tex.img.img || !game->ea_tex.img.img)
		return (false);
	return (true);
}

// mlx_do_key_autorepeatoff(game->mlx); //do i need this???
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
	if (!init_textures(game))
		cleanup(game, PRINT, ERR);
}

	// print_player(game); ->potentially after setup_player
void	game_loop(t_game *game)
{
	setup_player(game);
	init_mlx(game);
	init_hooks(game);
	mlx_loop(game->mlx);
}
