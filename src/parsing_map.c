/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 03:30:18 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/17 03:39:49 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

int	ft_mapchar(t_game *game, char *str, int fd)
{
	int	i;

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
			return (free(str), close(fd), 1);
		game->map.lin++;
		if ((int) ft_strlen(str) > game->map.col)
			game->map.col = ft_strlen(str);
		free(str);
		str = get_next_line(fd);
	}
	return (ft_checkeof(str, fd));
}

int	ft_emptyline(char **line, t_game *game, int fd)
{
	int		i;
	char	*str;

	str = *line;
	while (str)
	{
		i = -1;
		while (str[++i] && ft_isspace(str[i]))
			;
		if (str[i] != 0)
		{
			if (str[i] != '1')
				return (free(str), close(fd), 1);
			break ;
		}
		free(str);
		game->map.s_line++;
		str = get_next_line(fd);
	}
	*line = str;
	return (0);
}

void	ft_mapinfo(int fd, t_game *game, char *str)
{
	int	find;

	if (ft_emptyline(&str, game, fd) || ft_mapchar(game, str, fd))
	{
		ft_freeparse(game);
		ft_error("Error\nInvalid map\n");
	}
	fd = ft_open(game->file);
	if (ft_create_map(fd, game))
		ft_error("Error\nMalloc\n");
	find = ft_findo(game->map.map, game);
	while (find != -1)
	{
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
