/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:48:29 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/16 21:12:19 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_linux/mlx.h"
#include "../libft/include/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720

typedef struct s_col
{
	char	c;
	int		id;
}	t_col;

typedef struct s_wall
{
	int		info;
	int		x;
	int		y;
	t_col	*col;
	char	**wall;
}				t_wall;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_player
{
	double			posx;
	double			posy; //x and y start position
	double			dirx;
	double			diry; //initial direction vector
	double			planex;
	double			planey; //the 2d raycaster version of camera plane
	int				p_up;
	int				p_dw;
	int				p_lf;
	int				p_rg;
	int				left_r;
	int				right_r;
	struct s_game	*game;
}	t_player;

typedef struct s_map
{
	char	**map;
} t_map;

typedef struct s_game
{
	t_player	p1;
	t_map		map;
	t_img		img;
	t_wall		wall;
	t_wall		wall2;
	t_wall		wall3;
	t_wall		wall4;
	void		*mlx;
	void		*win;
}	t_game;

int	parse_xpm(t_wall *wall, char *file);
int	ft_atoi_base(char *str, char *base);