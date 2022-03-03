/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:04:37 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/02 16:53:40 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	tkn_alnum(t_data *data, int start, int cmd)
{
	int		i;
	t_tkn	*new;
	char	*dup;

	i = start;
	while (!ft_strchr(" <>$\"'", data->cmds[cmd].line[i])
			&& data->cmds[cmd].line[i])
		i++;
	dup = ft_strndup(data->cmds[cmd].line + start, i - start);
	if (!dup)
		return (-1);
	new = tkn_new(dup, TYPE_NAME);
	free(dup);
	if (!new)
		return (-1);
	if (data->cmds[cmd].line[i] == ' ')
		new->space = 1;
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (i - start);
}

int	tkn_quote(t_data *data, int start, int cmd)
{
	int		i;
	t_tkn	*new;
	char	*dup;

	i = start + 1;
	while (data->cmds[cmd].line[i] != '\''
			&& data->cmds[cmd].line[i])
		i++;
	dup = ft_strndup(data->cmds[cmd].line + start + 1, i - start - 1);
	if (!dup)
		return (-1);
	new = tkn_new(dup, TYPE_QUOTE);
	free(dup);
	if (!new)
		return (-1);
	if (data->cmds[cmd].line[i + 1] == ' ')
		new->space = 1;
	new->quotes = 1;
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (i - start + 1);
}

int	tkn_lessthan(t_data *data, int start, int cmd)
{
	t_tkn	*new;
	int		ret;

	if (data->cmds[cmd].line[start + 1] == '<')
	{
		new = tkn_new("<<", TYPE_HRDOC);
		if (!new)
			return (-1);
		ret = 2;
	}
	else
	{
		new = tkn_new("<", TYPE_REDIN);
		if (!new->content)
			return (-1);
		ret = 1;
	}
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (ret);
}

int	tkn_morethan(t_data *data, int start, int cmd)
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

int	tkn_var(t_data *data, int start, int cmd)
{
	t_tkn	*new;
	int		i;
	char	*dup;
	char	*var;

	i = start + 1;
	while (!ft_strchr(" <>$\"'", data->cmds[cmd].line[i])
			&& data->cmds[cmd].line[i])
		i++;
	dup = ft_strndup(data->cmds[cmd].line + start, i - start);
	if (!dup)
		return (-1);
	var = find_var(dup, data->env, data->exit_status);
	if (!var)
		return (-1);
	if (data->cmds[cmd].tkn && (tkn_last(data->cmds[cmd].tkn))->type == 6)
		new = tkn_new(dup, TYPE_VAR);
	else
		new = tkn_new(var, TYPE_VAR);
	free(dup);
	if (!new)
		return (-1);
	if (data->cmds[cmd].line[i] == ' ')
		new->space = 1;
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (i - start);
}
