/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:43:26 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/03 15:03:18 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quote(char *str)
{
	int	i;
	int	smpl;
	int	dbl;

	smpl = 0;
	dbl = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && dbl == 0 && smpl == 0)
			smpl = 1;
		else if (str[i] == '\'' && dbl == 0 && smpl == 1)
			smpl = 0;
		else if (str[i] == '"' && smpl == 0 && dbl == 0)
			dbl = 1;
		else if (str[i] == '"' && smpl == 0 && dbl == 1)
			dbl = 0;
		i++;
	}
	if (dbl + smpl != 0)
	{
		ft_putstr_fd("Syntax error: unclosed quotes", 2);
		g_g.exit = 2;
	}
	return (dbl + smpl);
}

int	split_cmds(t_data *data, char *str)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(str, '|');
	while (tab[i])
		i++;
	data->cmds = malloc(sizeof(t_cmd) * (i + 1));
	if (!data->cmds)
		return (-1);
	i = 0;
	while (tab[i])
	{
		data->cmds[i].line = ft_strdup(tab[i]);
		if (!data->cmds[i].line)
			return (-1);
		i++;
	}
	data->cmds[i].line = NULL;
	del_tab(tab);
	return (0);
}

int	spaces_between_tkns(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds[i].line)
	{
		if (merge_tokens(&data->cmds[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	merge_tokens(t_cmd *cmd)
{
	t_tkn	*cpy;

	cpy = cmd->tkn;
	while (cpy)
	{
		if (!cpy->space && cpy->next && cpy->next->type <= TYPE_VAR
				&& cpy->type <= TYPE_VAR)
		{
			if (merge_tokens2(cpy) == -1)
				return (-1);

		}
		else
			cpy = cpy->next;
	}
	return (0);
}

int	merge_tokens2(t_tkn *cpy)
{
	t_tkn	*tmp;
	char	*str;

	tmp = cpy->next;
	str = ft_strjoin(cpy->content, tmp->content);
	if (!str)
		return (-1);
	free(cpy->content);
	cpy->content = ft_strdup(str);
	free(str);
	if (!cpy->content)
		return (-1);
	cpy->space = tmp->space;
	cpy->quotes += tmp->quotes;
	if (tmp->next)
	{
		tmp->next->prev = tmp->prev;
		cpy->next = tmp->next;
	}
	else
		cpy->next = NULL;
	free(tmp->content);
	free(tmp);
	return (0);
}
