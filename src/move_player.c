/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 22:13:53 by dstumpf           #+#    #+#             */
/*   Updated: 2026/10/03 11:47:08 by dstumpf          ###   ########.fr       */
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

bool	is_wall(t_game *game, double x, double y)
{
	return (game->map.grid[(int)y][(int)x] == WALL);
}

static bool	hits_wall(t_game *game, double x, double y)
{
	return (is_wall(game, x - PLAYER_BODY, y - PLAYER_BODY)
		|| is_wall(game, x + PLAYER_BODY, y - PLAYER_BODY)
		|| is_wall(game, x - PLAYER_BODY, y + PLAYER_BODY)
		|| is_wall(game, x + PLAYER_BODY, y + PLAYER_BODY));
}

static void	translate(t_game *game, t_2d *dir, double step)
{
	t_2d	new_pos;

	new_pos = game->player.pos;
	new_pos.x += dir->x * step;
	new_pos.y += dir->y * step;
	if (!hits_wall(game, new_pos.x, game->player.pos.y))
		game->player.pos.x = new_pos.x;
	if (!hits_wall(game, game->player.pos.x, new_pos.y))
		game->player.pos.y = new_pos.y;
}

int	move_player(t_game *game, double t_diff)
{
	if (game->keys.w)
		translate(game, &game->player.dir, WALK * t_diff);
	if (game->keys.s)
		translate(game, &game->player.dir, -WALK * t_diff);
	if (game->keys.d)
		translate(game, &game->player.cam, WALK * t_diff);
	if (game->keys.a)
		translate(game, &game->player.cam, -WALK * t_diff);
	if (game->keys.left || game->keys.right)
	{
		if (game->keys.right)
			rotate(&game->player.dir, ROT * t_diff);
		else
			rotate(&game->player.dir, -ROT * t_diff);
		set_camera(game);
	}
	return (0);
}
