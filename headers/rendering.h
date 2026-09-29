/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 12:46:22 by dstumpf           #+#    #+#             */
/*   Updated: 2026/09/29 17:51:27 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H
# define X 0
# define Y 1

# include "data.h"

typedef enum e_face
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_face;

typedef struct s_hit
{
	double	dist;
	t_face	face;
}			t_hit;

typedef struct s_dda
{
	t_2d	ray_pos;
	t_2d	step_size;
	t_2d	step_dir;
	t_2d	ray_len;
	int		side;
}			t_dda;

//delete later
void	dummy_map(t_game *game);
void	print_map(t_game *game);
void	print_player(t_game *game);

//player functions
void	set_camera(t_game *game);
void	setup_player(t_game *game);

//moving the player around (rotate/translate);
//used inside mlx loop hook right before drawing
int		move_player(t_game *game);

//game
void	game_loop(t_game *game);
void	init_hooks(t_game *game);

//dda and drawing
void	raycast(t_game *game);
double	dda(t_game *game, t_2d *ray, int *side);

#endif
