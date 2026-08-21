/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_map_generator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 12:18:54 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/21 12:19:24 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "libft.h"
#include "ft_printf.h"

void	dummy_map(t_game *game)
{
	game->floor.r = 220;
	game->floor.g = 100;
	game->floor.b = 0;

	game->ceiling.r = 225;
	game->ceiling.g = 30;
	game->ceiling.b = 0;

	game->map.width = 33;
	game->map.height = 14;

	game->map.grid = malloc(sizeof(char *) * game->map.height);
	if (!game->map.grid)
		return ;

	game->map.grid[0] = ft_strdup("        1111111111111111111111111");
	game->map.grid[1] = ft_strdup("        1000000000110000000000001");
	game->map.grid[2] = ft_strdup("        1011000001110000000000001");
	game->map.grid[3] = ft_strdup("        1001000000000000000000001");
	game->map.grid[4] = ft_strdup("111111111011000001110000000000001");
	game->map.grid[5] = ft_strdup("100000000011000001110111111111111");
	game->map.grid[6] = ft_strdup("11110111111111011100000010001    ");
	game->map.grid[7] = ft_strdup("11110111111111011101010010001    ");
	game->map.grid[8] = ft_strdup("11000000110101011100000010001    ");
	game->map.grid[9] = ft_strdup("10000000000000001100000010001    ");
	game->map.grid[10] = ft_strdup("10000000000000001101010010001    ");
	game->map.grid[11] = ft_strdup("11000001110101011111011110N0111  ");
	game->map.grid[12] = ft_strdup("11110111 1110101 101111010001    ");
	game->map.grid[13] = ft_strdup("11111111 1111111 111111111111    ");
}

void	print_map(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		ft_printf(1, "%s\n", game->map.grid[y]);
		y++;
	}
}

void	print_player(t_game *game)
{
	printf("pos: %f %f\n", game->player.pos.x, game->player.pos.y);
	printf("dir: %f %f\n", game->player.dir.x, game->player.dir.y);
	printf("cam: %f %f\n", game->player.cam.x, game->player.cam.y);
}
