/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:19:43 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/17 17:05:50 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pars_morethan(t_data *data, int start, int cmd)
{
	t_tkn	*new;
	int		ret;

	if (data->cmds[cmd].line[start + 1] == '>')
	{
		new = tkn_new(">>", TYPE_APPEND);
		if (!new)
			return (-1);
		ret = 2;
	}
	else
	{
		new = tkn_new(">", TYPE_REDOUT);
		if (!new)
			return (-1);
		ret = 1;
	}
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (ret);
}

int	pars_var(t_data *data, int start, int cmd)
{
	t_tkn	*new;
	int		i;
	char	*dup;

	i = start + 1;
	while (!ft_strchr(" <>$\"'", data->cmds[cmd].line[i])
			&& data->cmds[cmd].line[i])
		i++;
	dup = ft_strndup(data->cmds[cmd].line + start, i - start);
	if (!dup)
		return (-1);
	new = tkn_new(dup, TYPE_VAR);
	free(dup);
	if (!new)
		return (-1);
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (i - start);
}
