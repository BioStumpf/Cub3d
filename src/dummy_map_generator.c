/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_map_generator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 12:18:54 by dstumpf           #+#    #+#             */
/*   Updated: 2026/11/10 14:33:58 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "libft.h"
#include "ft_printf.h"

void	dummy_map(t_game *game)
{
	game->ceiling = 220 << 16 | 100 << 8 | 0;
	game->floor = 225 << 16 | 30 << 8 | 0;

	game->map.width = 3;
	game->map.height = 60;

	game->no = "./textures/north_huge.xpm";
	game->so = "./textures/south.xpm";
	game->ea = "./textures/east.xpm";
	game->we = "./textures/west.xpm";

	game->map.grid = malloc(sizeof(char *) * game->map.height);
	if (!game->map.grid)
		return ;
	game->map.grid[0] = ft_strdup("111");
	game->map.grid[1] = ft_strdup("1S1");
	game->map.grid[2] = ft_strdup("101");
	game->map.grid[3] = ft_strdup("101");
	game->map.grid[4] = ft_strdup("101");
	game->map.grid[5] = ft_strdup("101");
	game->map.grid[6] = ft_strdup("101");
	game->map.grid[7] = ft_strdup("101");
	game->map.grid[8] = ft_strdup("101");
	game->map.grid[9] = ft_strdup("101");
	game->map.grid[10] = ft_strdup("101");
	game->map.grid[11] = ft_strdup("101");
	game->map.grid[12] = ft_strdup("101");
	game->map.grid[13] = ft_strdup("101");
	game->map.grid[14] = ft_strdup("101");
	game->map.grid[15] = ft_strdup("101");
	game->map.grid[16] = ft_strdup("101");
	game->map.grid[17] = ft_strdup("101");
	game->map.grid[18] = ft_strdup("101");
	game->map.grid[19] = ft_strdup("101");
	game->map.grid[20] = ft_strdup("101");
	game->map.grid[21] = ft_strdup("101");
	game->map.grid[22] = ft_strdup("101");
	game->map.grid[23] = ft_strdup("101");
	game->map.grid[24] = ft_strdup("101");
	game->map.grid[25] = ft_strdup("101");
	game->map.grid[26] = ft_strdup("101");
	game->map.grid[27] = ft_strdup("101");
	game->map.grid[28] = ft_strdup("101");
	game->map.grid[29] = ft_strdup("101");
	game->map.grid[30] = ft_strdup("101");
	game->map.grid[31] = ft_strdup("101");
	game->map.grid[32] = ft_strdup("101");
	game->map.grid[33] = ft_strdup("101");
	game->map.grid[34] = ft_strdup("101");
	game->map.grid[35] = ft_strdup("101");
	game->map.grid[36] = ft_strdup("101");
	game->map.grid[37] = ft_strdup("101");
	game->map.grid[38] = ft_strdup("101");
	game->map.grid[39] = ft_strdup("101");
	game->map.grid[40] = ft_strdup("101");
	game->map.grid[41] = ft_strdup("101");
	game->map.grid[42] = ft_strdup("101");
	game->map.grid[43] = ft_strdup("101");
	game->map.grid[44] = ft_strdup("101");
	game->map.grid[45] = ft_strdup("101");
	game->map.grid[46] = ft_strdup("101");
	game->map.grid[47] = ft_strdup("101");
	game->map.grid[48] = ft_strdup("101");
	game->map.grid[49] = ft_strdup("101");
	game->map.grid[50] = ft_strdup("101");
	game->map.grid[51] = ft_strdup("101");
	game->map.grid[52] = ft_strdup("101");
	game->map.grid[53] = ft_strdup("101");
	game->map.grid[54] = ft_strdup("101");
	game->map.grid[55] = ft_strdup("101");
	game->map.grid[56] = ft_strdup("101");
	game->map.grid[57] = ft_strdup("101");
	game->map.grid[58] = ft_strdup("101");
	game->map.grid[59] = ft_strdup("111");

	// game->map.grid[0] = ft_strdup("        1111111111111111111111111");
	// game->map.grid[1] = ft_strdup("        1000000000110000000000001");
	// game->map.grid[2] = ft_strdup("        1011000001110000000000001");
	// game->map.grid[3] = ft_strdup("        1001000000000000000000001");
	// game->map.grid[4] = ft_strdup("111111111011000001110000000000001");
	// game->map.grid[5] = ft_strdup("100000000011000001110111111111111");
	// game->map.grid[6] = ft_strdup("11110111111111011100000010001    ");
	// game->map.grid[7] = ft_strdup("11110111111111011101010010001    ");
	// game->map.grid[8] = ft_strdup("11000000110101011100000000001    ");
	// game->map.grid[9] = ft_strdup("10000000000000001100000010001    ");
	// game->map.grid[10] = ft_strdup("10000000000000001101010010001    ");
	// game->map.grid[11] = ft_strdup("11000001110101011111011110N0111  ");
	// game->map.grid[12] = ft_strdup("11110111 1110101 101111010001    ");
	// game->map.grid[13] = ft_strdup("11111111 1111111 111111111111    ");
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
