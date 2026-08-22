/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:58:52 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/22 15:15:30 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "rendering.h"
#include <math.h>

// void	pixel_to_img(t_imge *img, int x, int y, uint64_t color)
// {
// 	char	*pixel_addr;
// 	int		i;
//
// 	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
// 		return ;
// 	pixel_addr = img->addr + (y * img->len + x * img->bytes);
// 	i = -1;
// 	while (++i < img->bytes)
// 		pixel_addr[i] = (color >> (8 * i)) & 0xFF;
// }

t_2d	dda(t_game *game, t_2d *ray)
{
	t_dda	dda;

	dda.cur_point.x = floor(game->player.pos.x);
	dda.cur_point.y = floor(game->player.pos.y);
	dda.step_size.x = sqrt(1 + pow((ray->x / ray->y), 2));
	dda.step_size.y = sqrt(1 + pow((ray->y / ray->x), 2));
}

void	raycast(t_game *game)
{
	int		width;
	int		cam_x;
	t_2d	ray;
	t_2d	collision;

	width = -1;
	while (++width < WIDTH)
	{
		cam_x = 2 * width / WIDTH - 1;
		ray.x = game->player.dir.x + game->player.cam.x * cam_x;
		ray.y = game->player.dir.y + game->player.cam.y * cam_x;
		collision = dda(game, &ray);
		draw_column(game, &collision);
	}
}
