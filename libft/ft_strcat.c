/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:41:51 by aachbaro          #+#    #+#             */
/*   Updated: 2022/02/24 16:49:57 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!dst && !src)
		return (0);
	while (dst[i])
		i++;
	j = i;
	while (src[i - j])
	{
		dst[i] = src[i - j];
		i++;
	}
	return (dst);
}
