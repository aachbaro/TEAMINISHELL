/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:37:04 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/09 13:45:52 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*recup_var(t_data *data, int start, int cmd)
{
	char	*dup;
	char	*ret;
	int		i;

	i = start + 1;
	while (!ft_strchr(" <>$\"'", data->cmds[cmd].line[i])
		&& data->cmds[cmd].line[i])
		i++;
	dup = ft_strndup(data->cmds[cmd].line + start + 1, i - start);
	if (!dup)
		return (NULL);
	ret = find_var(dup, data->env, data->exit_status);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*find_var(char *var, t_envar *env, int exit_status)
{
	t_envar	*cpy;
	char	*ret;

	cpy = env;
	if (!ft_strncmp(var, "$", 1) && ft_strlen(var) == 1)
		return (ft_strdup("$"));
	if (!ft_strncmp(var, "$?", ft_strlen(var)))
		return (ft_itoa(exit_status));
	while (cpy)
	{
		if (!ft_strncmp(var + 1, cpy->str, ft_strlen(var + 1))
			&& cpy->str[ft_strlen(var + 1)] == '=')
			break ;
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
		pars->tmp = find_var(pars->str, data->env, data->exit_status);
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

void	empty_input(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds[i].line)
		i++;
	if (i == 1)
	{
		i = 0;
		while (data->cmds[0].line[i] == ' ')
			i++;
		if (data->cmds[0].line[i] == 0)
		{
			free(data->cmds[0].line);
			data->cmds[0].line = NULL;
		}
	}
}
