/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:04:37 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/09 14:28:40 by aachbaro         ###   ########.fr       */
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
	t_tkn				*new;
	t_dblquote_parser	p;

	p.i = start + 1;
	while (!ft_strchr(" <>$\"'", data->cmds[cmd].line[p.i])
		&& data->cmds[cmd].line[p.i])
		p.i++;
	p.tmp = ft_strndup(data->cmds[cmd].line + start, p.i - start);
	if (!p.tmp)
		return (-1);
	p.tmp2 = find_var(p.tmp, data->env, data->exit_status);
	if (!p.tmp2)
		return (-1);
	if (data->cmds[cmd].tkn && (tkn_last(data->cmds[cmd].tkn))->type == 6)
		new = tkn_new(p.tmp, TYPE_VAR);
	else
		new = tkn_new(p.tmp2, TYPE_VAR);
	free(p.tmp);
	free(p.tmp2);
	if (!new)
		return (-1);
	if (data->cmds[cmd].line[p.i] == ' ')
		new->space = 1;
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (p.i - start);
}
