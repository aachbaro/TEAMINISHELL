/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:30:16 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/15 12:58:29 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_empty_pipe(t_data *data)
{
	int	i;
	int	filled;
	int	not_empty;

	i = 0;
	filled = 1;
	while (data->usr_input[i])
	{
		if (data->usr_input[i] == '|' && filled == 0)
			return (ft_putstr_fd("Syntax error near '|'\n", 1), -1);
		if (data->usr_input[i] != ' ' && data->usr_input[i] != '|')
		{
			filled = 1;
			not_empty = 1;
		}
		else if (data->usr_input[i] == '|' && !not_empty)
			return (ft_putstr_fd("Syntax error near '|'\n", 1), -1);
		else if (data->usr_input[i] == '|')
			filled = 0;
		i++;
	}
	if (filled == 0 && not_empty)
		return (ft_putstr_fd("error: line ending with '|'\n", 1), -1);
	return (0);
}

int	chckinfsup(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds[i].line)
	{
		if (chckcmdinfsup(&data->cmds[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	chckcmdinfsup(t_cmd *cmd)
{
	t_tkn	*cpy;

	cpy = cmd->tkn;
	while (cpy)
	{
		if (cpy->type > TYPE_VAR
			&& (!cpy->next || cpy->next->type > TYPE_VAR))
		{
			ft_putstr_fd("Syntax error near unexpected token `", 1);
			if (!cpy->next)
				ft_putstr_fd("newline'\n", 1);
			else
			{
				ft_putstr_fd(cpy->next->content, 1);
				ft_putstr_fd("'\n", 1);
			}
			g_g.exit = 2;
			return (-1);
		}
		cpy = cpy->next;
	}
	return (0);
}
