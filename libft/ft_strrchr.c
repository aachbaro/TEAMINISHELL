/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <aachabaro@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:07:48 by aachbaro          #+#    #+#             */
/*   Updated: 2021/01/06 22:37:54 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i])
		i++;
	ptr = (char *)(s + i);
	while (i >= 0)
	{
		if (*ptr == (const char)c)
			return (ptr);
		i--;
		ptr--;
	}
	return (NULL);
}
