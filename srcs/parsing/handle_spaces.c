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
	t_tkn	*tmp;
	char	*str;

	cpy = cmd->tkn;
	while (cpy)
	{
		if (!cpy->space && cpy->next && cpy->next->type <= TYPE_VAR
				&& cpy->type <= TYPE_VAR)
		{
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
			if (tmp->next)
			{
				tmp->next->prev = tmp->prev;
				cpy->next = tmp->next;
			}
			else
				cpy->next = NULL;
			free(tmp->content);
			free(tmp);
		}
		else
			cpy = cpy->next;
	}
	return (0);
}
