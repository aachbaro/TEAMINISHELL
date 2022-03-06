/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:30:16 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/06 17:13:54 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_empty_pipe(t_data *data)
{
	int	i;
	int	filled;

	i = 0;
	filled = 0;
	while (data->usr_input[i])
	{
		if (data->usr_input[i] == '|' && filled == 0)
		{
			ft_putstr_fd("Syntax error near '|'\n", 1);
			return (-1);
		}
		if (data->usr_input[i] != ' ' && data->usr_input[i] != '|')
			filled = 1;
		else if (data->usr_input[i] == '|')
			filled = 0;
		i++;
	}
	if (filled == 0)
	{
		ft_putstr_fd("Syntax error: line ending with '|'\n", 1);	
		return (-1);
	}
	return (0);
}