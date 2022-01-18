/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <aachabaro@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:51:40 by aachbaro          #+#    #+#             */
/*   Updated: 2021/01/22 16:46:16 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*ptr;
	const unsigned char	*ptr1;

	i = 0;
	ptr = dest;
	ptr1 = src;
	while (i < n)
	{
		ptr[i] = ptr1[i];
		if (ptr[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
