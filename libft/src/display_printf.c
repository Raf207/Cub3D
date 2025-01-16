/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:05:13 by rafnasci          #+#    #+#             */
/*   Updated: 2024/02/25 13:27:50 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	count;

	if (!str)
	{
		if (write(1, "(null).", 6) == -1)
			return (-1);
		return (6);
	}
	count = 0;
	while (*str)
	{
		if (ft_putchar(*str++) == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_putnbr(int nb)
{
	char	*str;
	int		len;

	str = ft_itoa(nb);
	if (!str)
		return (free(str), -1);
	len = ft_putstr(str);
	free(str);
	return (len);
}

int	ft_putunsigned(unsigned int nb)
{
	char	*str;
	int		len;

	str = ft_uitoa(nb);
	if (!str)
		return (free(str), -1);
	len = ft_putstr(str);
	free(str);
	return (len);
}

int	ft_puthex(unsigned int nb, int case_t)
{
	char	*str;
	int		len;

	if (case_t == 0)
		str = ft_hexitoa(nb, "0123456789abcdef");
	else
		str = ft_hexitoa(nb, "0123456789ABCDEF");
	if (!str)
		return (free(str), -1);
	len = ft_putstr(str);
	free(str);
	return (len);
}
