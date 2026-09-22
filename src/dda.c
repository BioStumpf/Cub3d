/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 17:05:04 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/23 20:00:51 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "rendering.h"
#include <math.h>

static void	init_step_dir(t_2d *ray, t_dda *dda)
{
	if (ray->x < 0)
		dda->step_dir.x = -1;
	else
		dda->step_dir.x = 1;
	if (ray->y < 0)
		dda->step_dir.y = -1;
	else
		dda->step_dir.y = 1;
}

static void	init_ray_len(t_game *game, t_dda *dda)
{
	if (dda->step_dir.x < 0)
		dda->ray_len.x = (game->player.pos.x - dda->ray_pos.x)
			* dda->step_size.x;
	else
		dda->ray_len.x = ((dda->ray_pos.x + 1) - game->player.pos.x)
			* dda->step_size.x;
	if (dda->step_dir.y < 0)
		dda->ray_len.y = (game->player.pos.y - dda->ray_pos.y)
			* dda->step_size.y;
	else
		dda->ray_len.y = ((dda->ray_pos.y + 1) - game->player.pos.y)
			* dda->step_size.y;
}

static void	init_dda(t_game *game, t_2d *ray, t_dda *dda)
{
	dda->ray_pos.x = floor(game->player.pos.x);
	dda->ray_pos.y = floor(game->player.pos.y);
	dda->step_size.x = sqrt(1 + pow((ray->x / ray->y), 2));
	dda->step_size.y = sqrt(1 + pow((ray->y / ray->x), 2));
	init_step_dir(ray, dda);
	init_ray_len(game, dda);
}

t_2d	dda(t_game *game, t_2d *ray)
{
	t_dda	dda;

	init_dda(game, ray, &dda);
	while (true)
	{
		if (dda.ray_len.x < dda.ray_len.y)
		{
			dda.ray_pos.x += dda.step_dir.x;
			dda.ray_len.x += dda.step_size.x;
		}
		else
		{
			dda.ray_pos.y += dda.step_dir.y;
			dda.ray_len.y += dda.step_size.y;
		}
		if (game->map.grid[(int)dda.ray_pos.y][(int)dda.ray_pos.x] == 1)
			return ((t_2d){dda.ray_pos.x, dda.ray_pos.y});
	}
}
