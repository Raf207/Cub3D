/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:15:11 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/17 03:21:19 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	ft_setcolor(char *str, int len, t_game *game, int id)
{
	int	i;
	int	*rgb;

	ft_checkrgb(str, len);
	rgb = malloc (sizeof(int) * 3);
	if (!rgb)
		ft_error("Error\nMalloc");
	i = -1;
	if (++i < len)
	{
		rgb[0] = (int) ft_atorgb(&str[i]);
		while (ft_isdigit(str[i]) || ft_isspace(str[i]))
			i++;
		rgb[1] = (int) ft_atorgb(&str[++i]);
		while (ft_isdigit(str[i]) || ft_isspace(str[i]))
			i++;
		rgb[2] = (int) ft_atorgb(&str[++i]);
		while (ft_isdigit(str[i]) || ft_isspace(str[i]))
			i++;
	}
	if (id == 4)
		game->sprt.floor = rgb;
	else if (id == 5)
		game->sprt.ceiling = rgb;
}

void	ft_setid(char *str, int len, t_game *game, int id)
{
	int		i;
	int		img_width;
	int		img_height;
	char	*dup;
	void	*ptr;

	i = -1;
	while (str[++i + len] && ft_isspace(str[i + len]))
		;
	if (str[i + len])
		ft_error("Error\nInvalid identifier\n");
	dup = ft_strdup(str);
	dup[len] = 0;
	ptr = mlx_xpm_file_to_image(game->mlx, dup, &img_width, &img_height);
	free(dup);
	if (!ptr)
		ft_error("Error\nFail xpm to img\n");
	if (id == 0)
		game->sprt.north = ptr;
	else if (id == 1)
		game->sprt.south = ptr;
	else if (id == 2)
		game->sprt.east = ptr;
	else if (id == 3)
		game->sprt.west = ptr;
}

void	ft_getidentifier(char *str, t_game *game, int id)
{
	int		i;
	int		len;

	i = -1;
	if (str[++i])
	{
		while (ft_isspace(str[++i]))
			;
		if (str[i])
		{
			len = -1;
			while (str[i + (++len)] && !ft_isspace(str[i + len]))
				;
			if (id <= 3)
				ft_setid(&str[i], len, game, id);
			else
				ft_setcolor(&str[i], len, game, id);
		}
	}
}

void	ft_getinfo(char *str, t_game *game)
{
	int	i;

	i = -1;
	while (ft_isspace(str[++i]))
		;
	if (str[i] && str[i + 1])
	{
		if (str[i] == 'N' && str[i + 1] == 'O' && !game->sprt.north)
			ft_getidentifier(&str[i + 2], game, 0);
		else if (str[i] == 'S' && str[i + 1] == 'O' && !game->sprt.south)
			ft_getidentifier(&str[i + 2], game, 1);
		else if (str[i] == 'E' && str[i + 1] == 'A' && !game->sprt.east)
			ft_getidentifier(&str[i + 2], game, 2);
		else if (str[i] == 'W' && str[i + 1] == 'E' && !game->sprt.west)
			ft_getidentifier(&str[i + 2], game, 3);
		else if (str[i] == 'F' && !game->sprt.floor)
			ft_getidentifier(&str[i + 1], game, 4);
		else if (str[i] == 'C' && !game->sprt.ceiling)
			ft_getidentifier(&str[i + 1], game, 5);
		else
			ft_error("Error\nInvalid identifierff\n");
	}
}

void	parsing(char *file, t_game *game)
{
	int			fd;
	char		*line;
	t_sprites	*sprites;

	fd = ft_open(file);
	ft_init_pars(game);
	sprites = &game->sprt;
	line = get_next_line(fd);
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
