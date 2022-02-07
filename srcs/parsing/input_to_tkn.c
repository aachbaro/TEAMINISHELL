/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:43:26 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/22 16:01:13 by aachbaro         ###   ########.fr       */
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

int	str_to_tokens(char *str, t_data *data, int cmd)
{
	int		i;
	int		j;
	
	i = 0;
	while (str[i])
	{
		if (ft_strchr(" ", str[i]))
			j = 1; 
		else if (str[i] == '\'')
			j = pars_quote(data, i, cmd);
		else if (str[i] == '"')
			j = pars_dblquote(data, i, cmd);
		else if (str[i] == '<')
			j = pars_lessthan(data, i, cmd);
		else if (str[i] == '>')
			j = pars_morethan(data, i, cmd);
		else if (str[i] == '$')
			j = pars_var(data, i, cmd);
		else
			j = pars_alnum(data, i, cmd);
		if (j == -1)
			return (-1);
		i += j;
	}
	return (0);
}

int	input_to_tokens(t_data *data)
{
	int	i;

	i = 0;
	// Dans un premier temps je check que y ai pas derreur dans les quotes
	if (check_quote(data->usr_input))
		return (-1);
	// Ensuite je split sur le pipe
	if (split_cmds(data, data->usr_input) == -1)
		return (-1);
	// Ensuite je rempli la liste chainee de tkn a partir de chaque commandes
	while (data->cmds[i].line)
	{
		data->cmds[i].tkn = NULL;
		if (str_to_tokens(data->cmds[i].line, data, i) == -1)
			return (-1);
		i++;
	}
	if (spaces_between_tkns(data) == -1)
		return (-1);
	if (redir_in_tkns(data) == -1)
		return (-1);
	return (0);
}
