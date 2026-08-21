/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 10:16:32 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/21 14:23:22 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# define WIDTH 1000 
# define HEIGHT 800 
# define NOPRINT false 
# define PRINT true 
# define OK 0 
# define ERR 1 

# include <mlx.h>
# include <X11/keysym.h>
# include <stdbool.h>

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
	char	*addr;
	void	*img;
}			t_imge;

typedef struct s_2d
{
	double	x;
	double	y;
}			t_2d;

typedef struct s_player
{
	t_2d	pos;
	t_2d	dir;
	t_2d	cam;
}			t_player;

typedef struct s_game
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	void		*mlx;
	void		*win;
	t_player	player;
	t_imge		img;
}			t_game;

void	cleanup(t_game *game, bool print_err, int exit_status);

#endif
