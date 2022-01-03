/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:13:30 by aachbaro          #+#    #+#             */
/*   Updated: 2021/01/22 16:45:47 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == 0)
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s2[j] && s1[i + j] == s2[j] && (i + j) < len)
			j++;
		if (s2[j] == 0)
			return ((char *)(s1 + i));
		i++;
	}
	return (NULL);
}
