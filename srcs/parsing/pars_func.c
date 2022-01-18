/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:04:37 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/17 17:06:06 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pars_alnum(t_data *data, int start, int cmd)
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
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (i - start);
}

int	pars_quote(t_data *data, int start, int cmd)
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
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (i - start + 1);
}

int	pars_lessthan(t_data *data, int start, int cmd)
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

char	*recup_var(t_data *data, int start, int cmd)
{
	int	i;
	char	*dup;
	char	*ret;

	i = start + 1;
	while (!ft_strchr(" <>$\"'", data->cmds[cmd].line[i])
			&& data->cmds[cmd].line[i])
		i++;
	dup = ft_strndup(data->cmds[cmd].line + start + 1, i - start);
	if (!dup)
		return (NULL);
	ret = find_var(dup, data->env);
	if (!ret)
		return (NULL);
	return (ret);
}
