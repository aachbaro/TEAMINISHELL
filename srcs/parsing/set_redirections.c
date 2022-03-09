/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:51:59 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/09 17:54:04 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * redirection in tokens
 * this functions checks for redir and is called in parser.c
 */
int	redir_in_tkns(t_data *data)
{
	int	i;

	i = 0;
	data->heredoc_id = 0;
	while (data->cmds[i].line)
	{
		if (set_redir(&data->cmds[i]) == -1)
			return (-1);
		if (set_heredoc(&data->cmds[i], &data->heredoc_id, data))
			return (-1);
		i++;
	}
	return (0);
}

int	set_redir(t_cmd *cmd)
{
	t_tkn	*cpy;
	t_tkn	*tmp;

	cpy = cmd->tkn;
	while (cpy)
	{
		if (cpy->type >= TYPE_REDIN)
		{
			tmp = cpy->next;
			free(cpy->content);
			cpy->content = ft_strdup(cpy->next->content);
			cpy->quotes += cpy->next->quotes;
			if (!cpy->content)
				return (-1);
			if (cpy->next->next)
			{
				cpy->next->next->prev = cpy->next->prev;
				cpy->next = cpy->next->next;
			}
			else
				cpy->next = NULL;
			free(tmp->content);
			free(tmp);
		}
		cpy = cpy->next;
	}
	return (0);
}

int	set_heredoc(t_cmd *cmd, int *heredoc_id, t_data *data)
{
	t_tkn *cpy;
	int	hd_id;

	cpy = cmd->tkn;
	hd_id = *heredoc_id;
	while (cpy)
	{
		if (cpy->type == TYPE_HRDOC)
		{
			if (init_heredoc(cpy, hd_id, data))
				return (-1);
			hd_id++;
		}
		cpy = cpy->next;
	}
	*heredoc_id = hd_id;
	return (0);
}
