/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:20:43 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/17 03:41:42 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

int	ft_checkeof(char *str, int fd)
{
	int	i;

	i = -1;
	while (str)
	{
		i = -1;
		while (str[++i] && ft_isspace(str[i]))
			;
		if (str[i] != 0)
			return (free(str), close(fd), 1);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
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
	if (num > 255 || len > 10)
		ft_error("Error\nInvalid RBG value\n");
	return (num);
}

int	ft_routine(char *str, int i)
{
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i++] != ',' || (!ft_isdigit(str[i]) && !ft_isspace(str[i])))
		ft_error("Error\nInvalid identifier\n");
	while (ft_isspace(str[i]))
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i++] != ',' || (!ft_isdigit(str[i]) && !ft_isspace(str[i])))
		ft_error("Error\nInvalid identifier\n");
	while (ft_isspace(str[i]))
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

void	ft_checkrgb(char *str, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		i = ft_routine(str, i);
		len = i;
		if (str[i] && !ft_isspace(str[i]))
			ft_error("Error\nInvalid identifier\n");
	}
	i = -1;
	while (str[++i + len] && ft_isspace(str[i + len]))
		;
	if (str[i + len])
		ft_error("Error\nInvalid identifier\n");
}

void	ft_init_pars(t_game *game)
{
	game->sprt.floor = NULL;
	game->sprt.ceiling = NULL;
	game->sprt.north = NULL;
	game->sprt.south = NULL;
	game->sprt.east = NULL;
	game->sprt.west = NULL;
	game->map.bool_id = 0;
	game->map.s_line = 1;
	game->map.col = 0;
	game->map.lin = 0;
}
