/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 20:12:36 by dstumpf           #+#    #+#             */
/*   Updated: 2026/10/09 15:58:21 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include <stdlib.h>
#include <stdio.h>

static void	clean_mlx(t_game *game)
{
	if (game->no_tex.img.img)
		mlx_destroy_image(game->mlx, game->no_tex.img.img);
	if (game->so_tex.img.img)
		mlx_destroy_image(game->mlx, game->so_tex.img.img);
	if (game->we_tex.img.img)
		mlx_destroy_image(game->mlx, game->we_tex.img.img);
	if (game->ea_tex.img.img)
		mlx_destroy_image(game->mlx, game->ea_tex.img.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

//add this later, for now the paths are hardcoded
	// free(game->no);
	// free(game->so);
	// free(game->we);
	// free(game->ea);
void	cleanup(t_game *game, bool print_err, int exit_status)
{
	int	i;

	clean_mlx(game);
	i = 0;
	while (i < game->map.height)
		free(game->map.grid[i++]);
	free(game->map.grid);
	if (print_err)
		perror("Error\n");
	free(game->no);
	free(game->so);
	free(game->we);
	free(game->ea);
	exit (exit_status);
}
