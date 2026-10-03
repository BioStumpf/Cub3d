/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 17:05:04 by dstumpf           #+#    #+#             */
/*   Updated: 2026/10/03 11:50:38 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "rendering.h"
#include <math.h>

//the face_x and face_y indicate where the ray will hit the wall
//if me move -x, we move west, which means we will hit the wall east
//if me move -y (up), we move north, wall hit south
//this is important to know for the textures later
static void	init_step_dir(t_2d *ray, t_dda *dda)
{
	if (ray->x < 0)
	{
		dda->step_dir.x = -1;
		dda->face_x = EAST;
	}
	else
	{
		dda->step_dir.x = 1;
		dda->face_x = WEST;
	}
	if (ray->y < 0)
	{
		dda->step_dir.y = -1;
		dda->face_y = SOUTH;
	}
	else
	{
		dda->step_dir.y = 1;
		dda->face_y = NORTH;
	}
}

//ray_len.x and y represent the length to the next whole cell
//x is the length needed to traverse the next vertical line
//y is the lenght needed to traverse the next horizontal line
//if we step in -x, we initialize ray_len.x so that its the 
//the actual player position on the x axis (floating point number)
//minus the floored/rounded down player position/ray position
//this is the x distance, but we want to know the distance along
//the ray needed to travel to get there, so times step_size.x
//for positive x-step direction we add + 1 to the floored player
//position/ray position and subtrac the floating point player
//position from it, again multiplying by step size in x
//for y its the same
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

//this is the lenght of the vector to travel one unit into x/y direction
//i changed it to a normalizes step size, indicating how many
//vectors need to be traveled instead of their lenght which removes
//the fisheye
	// dda->step_size.x = sqrt(1 + pow((ray->y / ray->x), 2));
	// dda->step_size.y = sqrt(1 + pow((ray->x / ray->y), 2));
static void	init_dda(t_game *game, t_2d *ray, t_dda *dda)
{
	dda->ray_pos.x = floor(game->player.pos.x);
	dda->ray_pos.y = floor(game->player.pos.y);
	dda->step_size.x = 1 / fabs(ray->x);
	dda->step_size.y = 1 / fabs(ray->y);
	init_step_dir(ray, dda);
	init_ray_len(game, dda);
}

static void	calc_hit(t_dda *dda, t_hit *hit)
{
	if (hit->face == WEST || hit->face == EAST)
		hit->dist = dda->ray_len.x - dda->step_size.x;
	else
		hit->dist = dda->ray_len.y - dda->step_size.y;
}

// since ray len represents the distance to the next horizontal(ray_len.y)
// or vertical (ray_len.x) line, we just check whichever is closer
// and go one whole unit in that direction (x or y)
// that way we traverse all the cells accross our ray path
// once hitting the wall, we subtract one step size,
// since it indicates the distance to the next and not the current cell
// from the starting point
// this distance is what we return
void	dda(t_game *game, t_2d *ray, t_hit *hit)
{
	t_dda	dda;

	init_dda(game, ray, &dda);
	while (true)
	{
		if (dda.ray_len.x < dda.ray_len.y)
		{
			dda.ray_pos.x += dda.step_dir.x;
			dda.ray_len.x += dda.step_size.x;
			hit->face = dda.face_x;
		}
		else
		{
			dda.ray_pos.y += dda.step_dir.y;
			dda.ray_len.y += dda.step_size.y;
			hit->face = dda.face_y;
		}
		if (is_wall(game, dda.ray_pos.x, dda.ray_pos.y))
			break ;
	}
	return (calc_hit(&dda, hit));
}
