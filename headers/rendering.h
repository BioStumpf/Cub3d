/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 12:46:22 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/21 12:05:50 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "data.h"

//delete later
void	dummy_map(t_game *game);
void	print_map(t_game *game);
void	print_player(t_game *game);

//game loop
void	game_loop(t_game *game);

//player functions
void	set_camera(t_game *game);
void	setup_player(t_game *game);

#endif
