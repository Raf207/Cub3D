/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:20:10 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/16 18:20:17 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

int	ft_strlen2(char *str, char *base)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (base[j] != str[i] && base[j])
			j++;
		if (base[j] == str[i])
			i++;
		else
			return (i);
	}
	return (i);
}

int	ft_exposant(int nb, int exp)
{
	if (exp == 0)
		return (1);
	while (exp > 1)
	{
		return (nb * ft_exposant(nb, exp - 1));
	}
	return (nb);
}


int	ft_is_valid(char *base)
{
	int	i;
	int	j;
	//int	len_base;

	//len_base = ft_strlen2(base, base);
	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		if (base[i] == ' ' || base[i] == '\r' || base[i] == '\n'
			|| base[i] == '\f' || base[i] == '\v' || base[i] == '\t')
			return (0);
		i++;
	}
	return (i);
}

int	ft_putnbr_deci(char *str, char *base, int neg)
{
	int	len_base;
	int	len_str;
	int	i;
	int	j;
	int	nb;

	len_base = ft_strlen2(base, base);
	len_str = ft_strlen2(str, base);
	i = 0;
	nb = 0;
	while (str[i])
	{
		j = 0;
		while (base[j] != str[i] && base[j])
			j++;
		if (base[j] == str[i])
			nb = nb + (j * ft_exposant(len_base, len_str - i - 1));
		else
			return (nb * neg);
		i++;
	}
	return (neg * nb);
}

int	ft_atoi_base(char *str, char *base)
{
	int	is_neg;
	int	i;

	if (!ft_is_valid(base))
		return (0);
	is_neg = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\t')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_neg *= -1;
		i++;
	}
	return (ft_putnbr_deci(&str[i], base, is_neg));
}