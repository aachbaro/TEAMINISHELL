/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <aachabaro@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:59:45 by aachbaro          #+#    #+#             */
/*   Updated: 2021/01/22 12:56:27 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *s1, const void *s2, size_t n)
{
	int					i;
	unsigned char		*ptr;
	const unsigned char	*ptr1;

	i = 0;
	if (n == 0 || s1 == s2)
		return (0);
	ptr = (unsigned char *)s1;
	ptr1 = (unsigned char *)s2;
	while ((size_t)i < n)
	{
		if (*ptr != *ptr1)
			return (*ptr - *ptr1);
		i++;
		ptr++;
		ptr1++;
	}
	return (0);
}
