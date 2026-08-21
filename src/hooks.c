/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:26:13 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/21 15:41:16 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "data.h"

// static int	draw_img(void *param)
// {
// 	t_game	*game;
//
// 	game = (t_game *)param;
// 	ft_bzero(data->img->addr, data->img->len * HEIGHT);
// 	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
// 	return (0);
// }

static int	key_press(int keysym, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keysym == XK_Escape)
		mlx_loop_end(game->mlx);
	game->player.pos.x += (keysym == XK_w) * (game->player.dir.x * WALK_SPEED);
	game->player.pos.y += (keysym == XK_w) * (game->player.dir.y * WALK_SPEED);
	game->player.pos.x -= (keysym == XK_s) * (game->player.dir.x * WALK_SPEED);
	game->player.pos.y -= (keysym == XK_s) * (game->player.dir.y * WALK_SPEED);
	game->player.pos.x += (keysym == XK_d) * (game->player.cam.x * WALK_SPEED);
	game->player.pos.y += (keysym == XK_d) * (game->player.cam.y * WALK_SPEED);
	game->player.pos.x -= (keysym == XK_a) * (game->player.cam.x * WALK_SPEED);
	game->player.pos.y -= (keysym == XK_a) * (game->player.cam.y * WALK_SPEED);
	
	game->player.dir.x += (keysym == XK_Right) * (game->player.cam.x * SPEED);
	game->player.dir.y += (keysym == XK_Right) * (game->player.cam.y * SPEED);
	game->player.dir.x -= (keysym == XK_Left) * (game->player.cam.x * SPEED);
	game->player.dir.y -= (keysym == XK_Left) * (game->player.cam.y * SPEED);

	return (0);
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, &key_press, game);
	mlx_hook(game->win, 17, 0, mlx_loop_end, game->mlx);
	// mlx_loop_hook(game->mlx, draw_img, game);
}
