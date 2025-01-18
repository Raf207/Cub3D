/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 04:12:29 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/18 04:36:15 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

int	ft_findpalyer(char **map, t_game *game)
{
	int			y;
	int			x;

	y = -1;
	while (++y < game->map.lin)
	{
		x = -1;
		while (++x < game->map.col)
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				if (game->p1.posx == 0 && game->p1.posy == 0)
				{
					game->p1.posx == x;
					game->p1.posy == y;
				}
				else
					return (1);
			}
		}
	}
	return (0);
}

int	ft_findo(char **map, t_game *game)
{
	int			y;
	int			x;

	y = -1;
	while (++y < game->map.lin)
	{
		x = -1;
		while (++x < game->map.col)
		{
			if (map[y][x] == '0')
				return ((y * game->map.col) + x);
		}
	}
	return (-1);
}

int	ft_backtrack(int x, int y, t_game *game, char **plan)
{
	if (plan[y][x] == '1')
		return (0);
	if (x < 0 || x >= game->map.col || y < 0 || y >= game->map.lin
		|| plan[y][x] == ' ' || plan[y][x] == '\0')
		return (1);
	if (plan[y][x] == '0' || plan[y][x] == 'N' || plan[y][x] == 'S'
			|| plan[y][x] == 'E' || plan[y][x] == 'W')
	{
		plan[y][x] = 'V';
		if (ft_backtrack(x - 1, y, game, plan)
			|| ft_backtrack(x + 1, y, game, plan)
			|| ft_backtrack(x, y + 1, game, plan)
			|| ft_backtrack(x, y - 1, game, plan))
			return (1);
	}
	return (0);
}
