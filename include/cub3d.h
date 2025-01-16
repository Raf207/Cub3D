/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:56:45 by armitite          #+#    #+#             */
/*   Updated: 2025/01/16 18:14:35 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1080
#define PI 3.14159265359
#define CUBE 64
#define LEFT 65361
#define RIGHT 65363


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

typedef struct	s_player
{
	float	x;
	float	y;
	float	angle;
	
	int	p_up;
	int	p_dw;
	int	p_lf;
	int	p_rg;

	int	left_r;
	int	right_r;
}				t_player;

typedef struct	s_data 
{
	t_player	*player;
	t_wall		*wall;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	void	*test;
	char	**map;
	char	*addr;
	int		img_width;
	int		img_height;
	char	*relative_path;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	init_player(t_player *player);


//Parse xpm
int	parse_xpm(t_wall *wall, char **av);

//Draw && Draw_utils
int	draw_loop(t_data *data);
float fixed_dist(float x1, float y1, float x2, float y2, t_data *data);
float distance(float x, float y);
int	touch(float px, float py, t_data *data);

//Key hook
int	key_false(int keycode, t_player *player);
int	key_true(int keycode, t_player *player);
void	move_player(t_player *player);