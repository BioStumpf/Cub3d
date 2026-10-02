/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstumpf <dstumpf@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:14:09 by dstumpf           #+#    #+#             */
/*   Updated: 2026/10/02 12:19:34 by dstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# define WALL '1' 
# define WIDTH 1920
# define HEIGHT 1080
# define NOPRINT false 
# define PRINT true 
# define OK 0 
# define ERR 1 
# define WALK 2.7 
# define ROT 2.4
# define FPS 200.0

# include <mlx.h>
# include <X11/keysym.h>
# include <stdbool.h>

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

typedef struct s_tex
{
	int		width;
	int		height;
	t_imge	img;
}			t_tex;

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

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
}			t_keys;

typedef struct s_game
{
	int			floor;
	int			ceiling;
	t_keys		keys;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	t_map		map;
	double		last_frame;
	void		*mlx;
	void		*win;
	t_player	player;
	t_imge		img;
	t_tex		no_tex;
	t_tex		so_tex;
	t_tex		we_tex;
	t_tex		ea_tex;
}				t_game;

void	cleanup(t_game *game, bool print_err, int exit_status);

#endif
