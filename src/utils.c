/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:17:37 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/17 02:18:53 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

int	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Error\nFailed to open file\n");
	return (fd);
}
