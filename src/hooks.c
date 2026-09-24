/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:26:13 by dstumpf           #+#    #+#             */
/*   Updated: 2026/09/24 16:02:28 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <sys/time.h>
#include "data.h"
#include "libft.h"
#include "rendering.h"

static int	draw_img(void *param)
{
	struct timeval	tv;
	double			now;
	t_game			*game;

	game = (t_game *)param;
	gettimeofday(&tv, NULL);
	now = tv.tv_sec + tv.tv_usec / 1000000.0;
	if (now - game->last_frame < 1.0 / FPS)
		return (0);
	game->last_frame = now;
	move_player(game);
	ft_bzero(game->img.addr, game->img.len * HEIGHT);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

static void	set_key(t_game *game, int keysym, bool state)
{
	if (keysym == XK_w)
		game->keys.w = state;
	else if (keysym == XK_s)
		game->keys.s = state;
	else if (keysym == XK_d)
		game->keys.d = state;
	else if (keysym == XK_a)
		game->keys.a = state;
	else if (keysym == XK_Right)
		game->keys.right = state;
	else if (keysym == XK_Left)
		game->keys.left = state;
}

static int	key_press(int keysym, void *param)
{
	if (keysym == XK_Escape)
		mlx_loop_end(((t_game *)param)->mlx);
	set_key((t_game *)param, keysym, true);
	return (0);
}

static int	key_release(int keysym, void *param)
{
	set_key((t_game *)param, keysym, false);
	return (0);
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, &key_press, game);
	mlx_hook(game->win, 3, 1L << 1, &key_release, game);
	mlx_hook(game->win, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, draw_img, game);
}
