/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 20:12:36 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/20 20:27:55 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include <stdlib.h>

void	cleanup(t_game *game)
{
	int	i;

	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game->no);
	free(game->so);
	free(game->we);
	free(game->ea);
	i = 0;
	while (i < game->map.height)
		free(game->map.grid[i++]);
	free(game->map.grid);
}
