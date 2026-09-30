/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:58:52 by dstumpf           #+#    #+#             */
/*   Updated: 2026/09/30 17:26:57 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "rendering.h"
#include <stdint.h>
#include <math.h>

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

//cell_x represents where inside a cell we are in x horizontal direction
//if we face an east or western wall, that means 
//this horizontal direction is actually the y coordinates
//in our map. if e.g. we hit the wall at (2, 1.2)
//on an eastern facing wall, we are at 20% of the texture in x direction
//which gives us the texture column we need to draw
static void	set_texture(t_game *game, t_2d *ray, t_hit *hit,
		t_wall_tex *wall)
{
	double	cell_x;

	if (hit->face == EAST || hit->face == WEST)
		cell_x = game->player.pos.y + ray->y * hit->dist;
	else
		cell_x = game->player.pos.x + ray->x * hit->dist;
	if (hit->face == NORTH)
		wall->texture = &game->no_tex;
	else if (hit->face == SOUTH)
		wall->texture = &game->so_tex;
	else if (hit->face == EAST)
		wall->texture = &game->ea_tex;
	else if (hit->face == WEST)
		wall->texture = &game->we_tex;
	if (hit->face == NORTH || hit->face == EAST)
		wall->x = (ceil(cell_x) - cell_x) * wall->texture->width;
	else
		wall->x = (cell_x - floor(cell_x)) * wall->texture->width;
}

static int	tex_color(t_wall_tex *wall, int screen_y)
{
	t_tex	*t;
	int		wall_y;

	t = wall->texture;
	wall_y = (screen_y - wall->top) * t->height / wall->height;
	if (wall_y < 0)
		wall_y = 0;
	if (wall_y >= t->height)
		wall_y = t->height - 1;
	return (*(unsigned int *)(t->img.addr
		+ wall_y * t->img.len + wall->x * t->img.bytes));
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
static void	draw_wall(t_game *game, int screen_x, t_hit *hit, t_2d *ray)
{
	int			y;
	t_wall_tex	wall;

	if (hit->dist < 0.1)
		hit->dist = 0.1;
	wall.height = (int)(HEIGHT / hit->dist);
	wall.bottom = (HEIGHT + wall.height) / 2;
	wall.top = (HEIGHT - wall.height) / 2;
	set_texture(game, ray, hit, &wall);
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < wall.top)
			pixel_to_img(&game->img, screen_x, y, game->ceiling);
		else if (y > wall.bottom)
			pixel_to_img(&game->img, screen_x, y, game->floor);
		else
			pixel_to_img(&game->img, screen_x, y, tex_color(&wall, y));
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
		draw_wall(game, screen_x, &hit, &ray);
	}
}
