/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:58:52 by dstumpf           #+#    #+#             */
/*   Updated: 2026/09/30 12:53:47 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "rendering.h"
#include <stdint.h>

	// if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	// 	return ;
static void	pixel_to_img(t_imge *img, int x, int y, uint64_t color)
{
	char	*pixel_addr;
	int		i;

	pixel_addr = img->addr + (y * img->len + x * img->bytes);
	i = -1;
	while (++i < img->bytes)
		pixel_addr[i] = (color >> (8 * i)) & 0xFF;
}

// wall_height = (int)(HEIGHT / hit->dist);
//the further away the wall, the smaller

//why the center + halve of wall_height? 
//-> cause the image on screen is reversed, the top is at 0
//the bottom at HEIGHT
// wall_bottom = (HEIGHT + wall_height) / 2;
//HEIGHT / 2 + wall_height / 2 == (HEIGHT + wall_height) / 2

// wall_top = (HEIGHT - wall_height) / 2;
//HEIGHT / 2 - wall_height / 2 == (HEIGHT - wall_height) / 2
static void	draw_wall(t_game *game, int screen_x, t_hit *hit)
{
	int		wall_height;
	int		wall_bottom;
	int		wall_top;
	int		y;

	if (hit->dist < 0.1)
		hit->dist = 0.1;
	wall_height = (int)(HEIGHT / hit->dist);
	wall_bottom = (HEIGHT + wall_height) / 2;
	wall_top = (HEIGHT - wall_height) / 2;
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < wall_top)
			pixel_to_img(&game->img, screen_x, y, game->ceiling);
		else if (y > wall_bottom)
			pixel_to_img(&game->img, screen_x, y, game->floor);
		else
			pixel_to_img(&game->img, screen_x, y, 0xFFFFFF);
	}
}

void	raycast(t_game *game)
{
	int		screen_x;
	double	cam_x;
	t_2d	ray;
	t_hit	hit;

	screen_x = -1;
	while (++screen_x < WIDTH)
	{
		cam_x = 2.0 * screen_x / WIDTH - 1.0;
		ray.x = game->player.dir.x + game->player.cam.x * cam_x;
		ray.y = game->player.dir.y + game->player.cam.y * cam_x;
		dda(game, &ray, &hit);
		draw_wall(game, screen_x, &hit);
	}
}
