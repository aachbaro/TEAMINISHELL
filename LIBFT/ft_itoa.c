/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:59:11 by aachbaro          #+#    #+#             */
/*   Updated: 2021/09/01 15:40:18 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	power(int pow)
{
	long	i;
	long	res;

	i = 0;
	res = 1;
	while (i < pow)
	{
		res = res * 10;
		i++;
	}
	return (res);
}

long	numsize(long n, long i)
{
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	i;
	int		j;
	long	cpy;
	int		neg;

	j = 0;
	neg = 0;
	cpy = n;
	if (cpy < 0)
	{
		neg = 1;
		cpy = -cpy;
	}
	i = numsize(cpy, 1);
	str = malloc(sizeof(char) * (i + neg + 1));
	if (!str)
		return (NULL);
	if (neg == 1)
		str[j++] = '-';
	while (i > 0)
		str[j++] = ((cpy / power(i-- - 1)) % 10) + '0';
	str[j] = 0;
	return (str);
}
