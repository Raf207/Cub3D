/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:06:44 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/18 04:16:27 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	ft_freeparse(t_game *game)
{
	free(game->sprt.floor);
	free(game->sprt.ceiling);
	mlx_destroy_image(game->mlx, game->sprt.north);
	mlx_destroy_image(game->mlx, game->sprt.west);
	mlx_destroy_image(game->mlx, game->sprt.east);
	mlx_destroy_image(game->mlx, game->sprt.south);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	ft_freemap(char **map, t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map.lin)
		free(map[i]);
	free(map);
}
