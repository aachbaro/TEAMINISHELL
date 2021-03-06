/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:46:10 by aachbaro          #+#    #+#             */
/*   Updated: 2022/02/22 11:52:50 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * On fait un split de la ligne sur les pipe
 * Puis creer une liste chainee de token pour chaque "mot" de la commande
 * a la fin on a un tableau de commande qui contien pour chaque element:
 * la commande en entier en char*, le path de la commande, 
 * les arguments et la liste chainee de tkn, chaque tkn a un char* du "mot"
 * et le type du mot entre par rxemple "<<" ou une variable "$"
 * ces structures sont remplie dans les fonction line to token puis
 * tkn to exe, dans tkn\
 */

int	input_to_exe(t_data *data)
{
	int	i;

	i = 0;
	if (input_to_tokens(data) == -1)
		return (-1);
	while (data->cmds[i].line)
	{
		if (tkn_to_exe(data, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	input_to_tokens(t_data *data)
{
	int	i;

	i = 0;
	if (check_quote(data->usr_input))
		return (-1);
	if (split_cmds(data, data->usr_input) == -1)
		return (-1);
	while (data->cmds[i].line)
	{
		data->cmds[i].tkn = NULL;
		if (cmd_to_tokens(data->cmds[i].line, data, i) == -1)
			return (-1);
		i++;
	}
	if (spaces_between_tkns(data) == -1)
		return (-1);
	if (redir_in_tkns(data) == -1)
		return (-1);
	return (0);
}

int	cmd_to_tokens(char *str, t_data *data, int cmd)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(" ", str[i]))
			j = 1;
		else if (str[i] == '\'')
			j = tkn_quote(data, i, cmd);
		else if (str[i] == '"')
			j = tkn_dblquote(data, i, cmd);
		else if (str[i] == '<')
			j = tkn_lessthan(data, i, cmd);
		else if (str[i] == '>')
			j = tkn_morethan(data, i, cmd);
		else if (str[i] == '$')
			j = tkn_var(data, i, cmd);
		else
			j = tkn_alnum(data, i, cmd);
		if (j == -1)
			return (-1);
		i += j;
	}
	return (0);
}

int	tkn_to_exe(t_data *data, int cmd)
{
	t_tkn	*cpy;

	cpy = data->cmds[cmd].tkn;
	while (cpy->type > TYPE_VAR)
		cpy = cpy->next;
	data->cmds[cmd].path = get_path(cpy->content);
	if (!data->cmds[cmd].path)
		return (-1);
	data->cmds[cmd].args = get_args(data->cmds[cmd]);
	if (!data->cmds[cmd].args)
		return (-1);
	return (0);
}

