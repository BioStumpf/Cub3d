/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:58:52 by dstumpf           #+#    #+#             */
/*   Updated: 2026/09/22 16:12:13 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "rendering.h"
#include <math.h>
#include <stdint.h>

static void	pixel_to_img(t_imge *img, int x, int y, uint64_t color)
{
	char	*pixel_addr;
	int		i;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel_addr = img->addr + (y * img->len + x * img->bytes);
	i = -1;
	while (++i < img->bytes)
		pixel_addr[i] = (color >> (8 * i)) & 0xFF;
}

static void	draw_wall(t_game *game, t_2d *wall, int screen_x)
{
	int		wall_height;
	int		wall_bottom;
	int		wall_top;
	double	distance;

	distance = sqrt(pow(wall->x - game->player.pos.x, 2)
			+ pow(wall->y - game->player.pos.y, 2));
	wall_height = (int)(HEIGHT / distance);
	wall_bottom = (HEIGHT - wall_height) / 2;
	wall_top = (HEIGHT + wall_height) / 2;
	while (wall_bottom < wall_top)
		pixel_to_img(&game->img, screen_x, wall_bottom++, 0xFFFFFF);
}

void	raycast(t_game *game)
{
	int		screen_x;
	double	cam_x;
	t_2d	ray;
	t_2d	wall;

	screen_x = -1;
	while (++screen_x < WIDTH)
	{
		cam_x = 2.0 * screen_x / WIDTH - 1.0;
		ray.x = game->player.dir.x + game->player.cam.x * cam_x;
		ray.y = game->player.dir.y + game->player.cam.y * cam_x;
		wall = dda(game, &ray);
		draw_wall(game, &wall, screen_x);
	}
}
