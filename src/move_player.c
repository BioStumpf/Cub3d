/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 22:13:53 by dstumpf           #+#    #+#             */
/*   Updated: 2026/09/22 22:18:27 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "data.h"
#include "rendering.h"

static void	rotate(t_2d *vector, double angle)
{
	double	x;
	double	y;

	x = vector->x;
	y = vector->y;
	vector->x = x * cos(angle) - y * sin(angle);
	vector->y = x * sin(angle) + y * cos(angle);
}

static void	translate(t_game *game, t_2d *dir, double step)
{
	t_2d	new_pos;

	new_pos = game->player.pos;
	new_pos.x += dir->x * step;
	new_pos.y += dir->y * step;
	if (game->map.grid[(int)new_pos.y][(int)new_pos.x] != WALL)
		game->player.pos = new_pos;
}

int	move_player(t_game *game)
{
	if (game->keys.w)
		translate(game, &game->player.dir, WALK);
	if (game->keys.s)
		translate(game, &game->player.dir, -WALK);
	if (game->keys.d)
		translate(game, &game->player.cam, WALK);
	if (game->keys.a)
		translate(game, &game->player.cam, -WALK);
	if (game->keys.left || game->keys.right)
	{
		if (game->keys.right)
			rotate(&game->player.dir, ROT);
		else
			rotate(&game->player.dir, -ROT);
		set_camera(game);
	}
	return (0);
}
