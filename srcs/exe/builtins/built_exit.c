/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:04:19 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/03 14:36:24 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	built_exit(t_cmd cmd, t_data data)
{
	t_tkn	*cpy;
	int	i;

	cpy = cmd.tkn;
	i = 0;
	while (cpy)
	{
		if (cpy->type <= TYPE_QUOTE)
			i++;
		cpy = cpy->next;
	}
	if (i > 2)
	{
		ft_putstr_fd("Shell: exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	data->over = 1;
	i = 0;
	while (
}
