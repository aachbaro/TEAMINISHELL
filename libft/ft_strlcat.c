/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:41:51 by aachbaro          #+#    #+#             */
/*   Updated: 2021/01/15 10:26:10 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!dst && !src)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i])
		i++;
	j = i;
	while (src[i - j] && i < size - 1)
	{
		dst[i] = src[i - j];
		i++;
	}
	if (size < j)
		return (size + ft_strlen(src));
	if (j < size)
		dst[i] = 0;
	return (j + ft_strlen(src));
}
