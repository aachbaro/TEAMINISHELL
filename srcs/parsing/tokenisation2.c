/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:46:10 by aachbaro          #+#    #+#             */
/*   Updated: 2022/02/24 13:50:18 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	tkn_dblquote(t_data *data, int start, int cmd)
{
	t_dblquote_parser	pars;
	t_tkn			*new;

	pars.i = start + 1;
	pars.str = ft_strdup("");
	if (!pars.str)
		return (-1);
	while (data->cmds[cmd].line[pars.i]
			&& data->cmds[cmd].line[pars.i] != '"')
	{
		if (in_loop(data, cmd, &pars) == -1)
			return (-1);
	}
	new = tkn_new(pars.str, TYPE_DBLQUOTE);
	if (!new)
		return (-1);
	if (data->cmds[cmd].line[pars.i + 1] == ' ')
		new->space = 1;
	new->quotes = 1;
	free(pars.str);
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (pars.i - start + 1);
}
