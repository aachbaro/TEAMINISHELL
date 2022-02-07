/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:51:59 by ababaei           #+#    #+#             */
/*   Updated: 2022/01/14 18:20:46 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redir_in_tkns(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds[i].line)
	{
		if (set_redir(&data->cmds[i]) == -1)
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
