/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:46:10 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/17 18:11:36 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_var(char *var, t_envar *env)
{
	t_envar	*cpy;
	char	*ret;

	cpy = env;
	while (cpy)
	{
		if (!ft_strncmp(var + 1, cpy->str, ft_strlen(var + 1))
				&& cpy->str[ft_strlen(var + 1)] == '=')
			break;
		cpy = cpy->next;
	}
	if (cpy)
	{
		ret = ft_strdup(cpy->str + ft_strlen(var + 1) + 1);
		if (!ret)
			return (NULL);
	}
	else
		ret = ft_strdup("");
	return (ret);
}

int	pars_var(t_data *data, int start, int cmd)
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
	var = find_var(dup, data->env);
	if (!var)
		return (-1);
	new = tkn_new(var, TYPE_VAR);
	if (!new)
		return (-1);
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (i - start);
}

int	get_tmp_dbl(t_data *data, int cmd, t_dblquote_parser *pars)
{
	if (data->cmds[cmd].line[pars->i] == '$')
	{
		pars->j++;
		while (!ft_strchr(" <>$\"'", data->cmds[cmd].line[pars->j])
			&& data->cmds[cmd].line[pars->j])
			pars->j++;
		pars->str = ft_strndup(data->cmds[cmd].line + pars->i,
				pars->j - pars->i);
		if (!pars->str)
			return (-1);
		pars->tmp = find_var(pars->str, data->env);
		free(pars->str);
		if (!pars->tmp)
			return (-1);
	}
	else
	{
		while (!ft_strchr("$\"", data->cmds[cmd].line[pars->j]))
			pars->j++;
		pars->tmp = ft_strndup(data->cmds[cmd].line + pars->i,
				pars->j - pars->i);
		if (!pars->tmp)
			return (-1);
	}
	return (0);
}

int	in_loop(t_data *data, int cmd, t_dblquote_parser *pars)
{
	pars->tmp2 = ft_strdup(pars->str);
	free(pars->str);
	if (!pars->tmp)
		return (-1);
	pars->j = pars->i;
	if (get_tmp_dbl(data, cmd, pars) == -1)
		return (-1);
	pars->str = ft_strjoin(pars->tmp2, pars->tmp);
	free(pars->tmp);
	free(pars->tmp2);
	if (!pars->str)
		return (-1);
	pars->i = pars->j;
	return (0);
}

int	pars_dblquote(t_data *data, int start, int cmd)
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
	free(pars.str);
	tkn_addback(&data->cmds[cmd].tkn, new);
	return (pars.i - start + 1);
}
