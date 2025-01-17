/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:43:45 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/17 02:03:26 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../mlx_linux/mlx.h"
#include "../libft/include/libft.h"

typedef struct s_sprites
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	int		*floor;
	int		*ceiling;
}	t_sprites;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_map
{
	char	**map;
	int		bool_id;
	int		s_line;
	int		lin;
	int		col;
}	t_mapdata;

typedef struct s_game
{
	char		*file;
	t_mlx		mlx;
	t_sprites	sprites;
	t_mapdata	map;
}	t_game;