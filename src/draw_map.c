/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:58:52 by dstumpf           #+#    #+#             */
/*   Updated: 2026/10/03 11:23:44 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "rendering.h"
#include <stdint.h>
#include <math.h>

	// if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	// 	return ;
static void	pixel_to_img(t_imge *img, int x, int y, uint32_t color)
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
//on an western facing wall, we are at 20% of the texture in x direction
//which gives us the texture column we need to draw
//if our ray hit a wall facing NORTH or EAST, we need to reverse the
//x coordinate.
//e.g. if we look at a wall facing NORTH, we ourselfs face south,
//meaning the maps x axis is inverted (the texture needs to be drawn
//left to right, while our x axis goes from right to left)
//so in these cases we take the distance to the ceiled actual coordinate
//e.g.: 1.2: ceil(1.2) - 1.2 = 0.8
//while in the other cases we would take 0.2 as the fraction
//note: hit->face is where the wall itself faces not the player
static void	set_texture(t_game *game, t_2d *ray, t_hit *hit,
		t_wall_tex *wall)
{
	double	cell_x;

	if (hit->face == EAST || hit->face == WEST)
		cell_x = game->player.pos.y + ray->y * hit->dist;
	else
		cell_x = game->player.pos.x + ray->x * hit->dist;
	if (hit->face == NORTH)
		wall->texture = &game->so_tex;
	else if (hit->face == SOUTH)
		wall->texture = &game->no_tex;
	else if (hit->face == EAST)
		wall->texture = &game->we_tex;
	else if (hit->face == WEST)
		wall->texture = &game->ea_tex;
	if (hit->face == NORTH || hit->face == EAST)
		wall->x = (ceil(cell_x) - cell_x) * wall->texture->width;
	else
		wall->x = (cell_x - floor(cell_x)) * wall->texture->width;
}

//so first we alrady know that our screen y is inside the wall cooords
//cause we only go inside this funcion once the else statement
//in draw_wall is triggered
//so screen_y > wall->top.
//to normalize the wall coordinates from 0 to wall_height, we subtract wall->top
//(remember the screen draws top to bottom so the top has lower coords)
//from that coordinate.
//once done, we divide by wall->height, which gives us a percentage.
//that percentage multiplied by t->height (texture height)
//gives the y coordinate of that specific texture
//once that is done, we mutliply with the factor:
//t->height / wall->height, which normalizes the textures height
//with respect to our wall height.
//
static uint32_t	tex_color(t_wall_tex *wall, int screen_y)
{
	t_tex	*t;
	int		wall_y;

	t = wall->texture;
	wall_y = (screen_y - wall->top) * t->height / wall->height;
	return (*(uint32_t *)(t->img.addr
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
		else if (y >= wall.bottom)
			pixel_to_img(&game->img, screen_x, y, game->floor);
		else
			pixel_to_img(&game->img, screen_x, y, tex_color(&wall, y));
	}
}

// so we iterate through the entire screen width and compute 
// a normalized camera_x position between -1 and 1
// using the players camera vector, we multiply this scalar
// camera x coordinate with that camera vector, iteratively
// giving the cam vector a range of lenght
// adding this to the players view direction gives the ray vector
// hence the direction the ray is pointing in (and an unnormalized lenght)
// using this ray, we do dda, ergo we scan every cell along this ray until
// hitting an obstacle
// the length returned from dda is then used to scale the height of the
// wall that was just hit
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
