/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 16:05:12 by aachbaro          #+#    #+#             */
/*   Updated: 2021/03/10 12:19:13 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long	cpy;

	cpy = nb;
	if (cpy < 0)
	{
		ft_putchar_fd('-', fd);
		cpy = -cpy;
	}
	if (cpy > 9)
		ft_putnbr_fd(cpy / 10, fd);
	ft_putchar_fd(cpy % 10 + '0', fd);
}
