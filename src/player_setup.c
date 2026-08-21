/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 11:37:47 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/21 14:22:22 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
// #include "rendering.h"

static bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static void	find_player(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			if (is_player(game->map.grid[i][j]))
			{
				game->player.pos.x = j;
				game->player.pos.y = i;
				return ;
			}
		}
	}
}

static void	set_direction(t_game *game)
{
	char	dir;

	dir = game->map.grid[(int)game->player.pos.y][(int)game->player.pos.x];
	if (dir == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
	}
	else if (dir == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
	}
	else if (dir == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
	}
	else if (dir == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
	}
}

void	set_camera(t_game *game)
{
	game->player.cam.x = -game->player.dir.y * 0.66;
	game->player.cam.y = game->player.dir.x * 0.66;
}

void	setup_player(t_game *game)
{
	find_player(game);
	set_direction(game);
	set_camera(game);
}
