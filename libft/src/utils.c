/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:23:12 by rafnasci          #+#    #+#             */
/*   Updated: 2024/02/25 13:28:01 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_invert(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = ft_strlen(str);
	if (str[i] == '-')
		i++;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len - 1];
		str[len - 1] = tmp;
		i++;
		len--;
	}
	return (str);
}

static int	ft_unsignedlen(unsigned long n)
{
	int	len;

	if (n <= 0)
	{
		len = 1;
		n *= -1;
	}
	else
		len = 0;
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	int				len;
	char			*rep;
	unsigned long	nb;

	nb = n;
	len = ft_unsignedlen(nb);
	rep = ft_calloc(len + 1, sizeof(char));
	if (!rep)
		return (NULL);
	len = 0;
	rep[len] = '0';
	while (nb > 0)
	{
		rep[len] = nb % 10 + '0';
		nb = nb / 10;
		len++;
	}
	return (ft_invert(rep));
}

static int	ft_hexalen(long nb)
{
	int	len;

	if (nb == 0)
		return (1);
	len = 0;
	while (nb > 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

char	*ft_hexitoa(unsigned int n, char *base)
{
	int		len;
	char	*rep;
	long	nb;

	nb = n;
	len = ft_hexalen(nb);
	rep = ft_calloc(len + 1, sizeof(char));
	if (!rep)
		return (NULL);
	len = 0;
	rep[len] = '0';
	while (nb > 0)
	{
		rep[len] = base[nb % 16];
		nb = nb / 16;
		len++;
	}
	return (ft_invert(rep));
}
