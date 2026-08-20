/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 10:16:32 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/20 12:11:38 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <mlx.h>
# include <X11/keysym.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
}			t_map;

typedef struct s_imge
{
	int		bits;
	int		bytes;
	int		len;
	int		end;
	int		color;
	char	*addr;
	void	*img;
}			t_imge;

typedef struct s_game
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	floor;
	t_color	ceiling;
	t_map	map;
	void	*mlx;
	void	*win;
	t_imge	img;
}			t_game;

#endif
