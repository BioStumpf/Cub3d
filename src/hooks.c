/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:26:13 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/22 10:40:04 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "data.h"
#include "rendering.h"

// static int	draw_img(void *param)
// {
// 	t_game	*game;
//
// 	game = (t_game *)param;
// 	ft_bzero(data->img->addr, data->img->len * HEIGHT);
// 	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
// 	return (0);
// }

static void	rotate(t_2d *vector, double angle)
{
	double	x;
	double	y;

	x = vector->x;
	y = vector->y;
	vector->x = x * cos(angle) - y * sin(angle);
	vector->y = x * sin(angle) + y * cos(angle);
}

static void	translate(t_2d *pos, t_2d *dir, double step)
{
	pos->x += dir->x * step;
	pos->y += dir->y * step;
}

static int	key_press(int keysym, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keysym == XK_Escape)
		mlx_loop_end(game->mlx);
	if (keysym == XK_w)
		translate(&game->player.pos, &game->player.dir, WALK);
	else if (keysym == XK_s)
		translate(&game->player.pos, &game->player.dir, -WALK);
	else if (keysym == XK_d)
		translate(&game->player.pos, &game->player.cam, WALK);
	else if (keysym == XK_a)
		translate(&game->player.pos, &game->player.cam, -WALK);
	else if (keysym == XK_Right || keysym == XK_Left)
	{
		if (keysym == XK_Right)
			rotate(&game->player.dir, ROT);
		else
			rotate(&game->player.dir, -ROT);
		set_camera(game);
	}
	return (0);
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, &key_press, game);
	mlx_hook(game->win, 17, 0, mlx_loop_end, game->mlx);
	// mlx_loop_hook(game->mlx, draw_img, game);
}
