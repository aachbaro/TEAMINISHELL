/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:09:10 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/02 15:23:37 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_error(char *msg, int exit_num)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	g_glob.exit = exit_num;
	return (EXIT_FAILURE);
}
