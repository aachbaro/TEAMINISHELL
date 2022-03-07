/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:30:16 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/07 17:06:33 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_empty_pipe(t_data *data)
{
	int	i;
	int	filled;
	int	not_empty;

	i = 0;
	filled = 2;
	while (data->usr_input[i])
	{
		if (data->usr_input[i] == '|' && filled == 0)
		{
			ft_putstr_fd("Syntax error near '|'\n", 1);
			return (-1);
		}
		if (data->usr_input[i] != ' ' && data->usr_input[i] != '|')
		{
			filled = 1;
			not_empty = 1;
		}
		else if (data->usr_input[i] == '|')
			filled = 0;
		i++;
	}
	if (filled == 0 && not_empty)
	{
		ft_putstr_fd("Syntax error: line ending with '|'\n", 1);	
		return (-1);
	}
	return (0);
}
