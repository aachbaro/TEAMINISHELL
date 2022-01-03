/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frag_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:53:44 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/17 17:05:08 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tkn	*tkn_new(char *content, int type)
{
	t_tkn	*new;

	new = malloc(sizeof(t_tkn));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_tkn	*tkn_last(t_tkn *cmd)
{
	t_tkn	*cpy;

	cpy = cmd;
	if (cpy)
		while (cpy->next)
			cpy = cpy->next;
	return (cpy);
}

void	tkn_addback(t_tkn **cmd, t_tkn *new)
{
	t_tkn	*cpy;

	if (*cmd == NULL)
		*cmd = new;
	else
	{
		cpy = tkn_last(*cmd);
		cpy->next = new;
		cpy->next->prev = cpy;
	}
}

void	tkn_clear(t_tkn **cmd)
{
	t_tkn	*cpy;

	while (*cmd)
	{
		cpy = (*cmd)->next;
		free((*cmd)->content);
		free(*cmd);
		*cmd = cpy;
	}
}
