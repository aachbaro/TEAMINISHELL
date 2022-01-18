/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <aachabaro@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:20:04 by aachbaro          #+#    #+#             */
/*   Updated: 2021/01/22 12:12:41 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptr;

	ptr = (char *)dest;
	if (!dest && !src)
		return (NULL);
	while (n != 0)
	{
		*(char *)ptr = *(char *)src;
		n--;
		ptr++;
		src++;
	}
	return (dest);
}
