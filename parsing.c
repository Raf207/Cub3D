/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:43:58 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/17 03:32:22 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void ft_freeall(t_game *game)
{
	free(game->sprites.floor);
	free(game->sprites.ceiling);
	mlx_destroy_image(game->mlx.mlx, game->sprites.north);
	mlx_destroy_image(game->mlx.mlx, game->sprites.west);
	mlx_destroy_image(game->mlx.mlx, game->sprites.east);
	mlx_destroy_image(game->mlx.mlx, game->sprites.south);
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	mlx_destroy_display(game->mlx.mlx);
	free(game->mlx.mlx);
}

long	ft_atorgb(char *str)
{
	int		i;
	long	num;
	int		len;

	i = -1;
	while (ft_isspace(str[++i]))
		;
	if (!ft_isdigit(str[i]) && str[i] != '+')
		ft_error("Error\nInvalid RBG value\n");
	num = 0;
	len = 0;
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		++len;
		num = (num * 10) + (str[i++] - '0');
	}
	// if (str[i] != 0)
	// 	ft_error("Error\nInvalid RBG value\n");
	if (num > 255 || len > 10)
		ft_error("Error\nInvalid RBG value\n");
	return (num);
}

void	gameloop(t_game *game)
{
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->sprites.north, 0, 0);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->sprites.south, 64, 0);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->sprites.east, 64 * 2, 0);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->sprites.west, 64 * 3, 0);
	mlx_loop(game->mlx.mlx);
}

int ft_checkeof(char *str, int fd)
{
	int	i;

	i = -1;
	while (str)
	{
		i = -1;
		while (str[++i] && ft_isspace(str[i]))
			;
		if (str[i] != 0)
			return (free(str), 1);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	ft_mapchar(t_game *game, char *str, int fd)
{
	int	i;

	i = -1;
	while (str)
	{
		i = -1;
		while (str[++i] && ft_isspace(str[i]))
			;
		if (str[i] == 0)
			break ;
		i = -1;
		while (str[++i] && (ft_isspace(str[i]) || str[i] == '0' || str[i] == '1'
				|| str[i] == 'N' || str[i] == 'S'
				|| str[i] == 'W' || str[i] == 'E'))
				;
		if (str[i] && str[i] != '\n')
			return (free(str), 1);
		game->map.lin++;
		if ((int) ft_strlen(str) > game->map.col)
			game->map.col = ft_strlen(str);
		free(str);
		str = get_next_line(fd);
	}
	return (ft_checkeof(str, fd));
}

int ft_create_map(int fd, t_game *game)
{
	char	*str;
	int		i;

	i = -1;
	str = get_next_line(fd);
	while (++i < game->map.s_line - 1)
	{
		free(str);
		str = get_next_line(fd);
	}
	game->map.map = malloc(sizeof(char *) * game->map.lin);
	if (!game->map.map)
		return (ft_freeall(game), 1);
	i = -1;
	while (++i < game->map.lin)
	{
		game->map.map[i] = calloc(sizeof(char), game->map.col + 1);
		if (!game->map.map[i])
			return (free(game->map.map), ft_freeall(game), 1);
		ft_strlcpy(game->map.map[i], str, ft_strlen(str) + 1);
		free(str);
		str = get_next_line(fd);
	}
	return (close(fd), free(str), 0);
}

int	ft_backtrack(int x, int y, t_game * game, char **plan)
{
	if (plan[y][x] == '1')
		return (0);
	if (x < 0 || x >= game->map.col || y < 0 || y >= game->map.lin || plan[y][x] == ' ' || plan[y][x] == '\0')
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

int	ft_findo(char **map, t_game *game)
{
	int	y;
	int	x;

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

void	ft_freemap(char **map, t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map.lin)
		free(map[i]);
	free(map);
}

void ft_mapinfo(int fd, t_game *game, char *str)
{
	int	find;

	if (ft_emptyline(&str, game, fd) || ft_mapchar(game, str, fd))
	{
		ft_freeall(game);
		ft_error("Error\nInvalid map\n");
	}
	fd = ft_open(game->file);
	if (ft_create_map(fd, game))
		ft_error("Error\nMalloc\n");
	find = ft_findo(game->map.map, game);
	while (find != -1)
	{
		printf("find : %d\n", find);
		if (ft_backtrack(find % game->map.col, find / game->map.col,
				game, game->map.map))
		{
			ft_freemap(game->map.map, game);
			ft_freeall(game);
			ft_error("Error\nInvalid map\n");
		}
		find = ft_findo(game->map.map, game);
	}
	ft_freemap(game->map.map, game);
}

void	parsing(char *file, t_game *game)
{
	int			fd;
	char		*line;
	t_sprites	*sprites;

	fd = ft_open(file);
	ft_init_pars(game);
	line = get_next_line(fd);
	sprites = &game->sprites;
	while (line && !game->map.bool_id)
	{
		ft_getinfo(line, game);
		free(line);
		line = get_next_line(fd);
		if (sprites->ceiling && sprites->floor && sprites->north
			&& sprites->south && sprites->east && sprites->west)
			game->map.bool_id = 1;
		game->map.s_line++;
	}
	ft_mapinfo(fd, game, line);
}
