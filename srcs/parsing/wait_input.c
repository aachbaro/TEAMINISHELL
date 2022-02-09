/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:51:59 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/08 16:52:57 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * input.c
 * Here we have the main loop waiting for an input and then processing it
 * until the shell is over.
 * check readme for g_status values meaning.
 * this function is called in the return of main.c
 */

void	aff_tkn(t_data data)
{
	int	i;
	t_tkn	*cpy;

	i = 0;
	while (data.cmds[i].line)
	{
		printf("%d :\n", i);
		cpy = data.cmds[i].tkn;
		while (cpy)
		{
			printf("content = %s\ntype = %d\n\n", cpy->content, cpy->type);
			cpy = cpy->next;
		}
		i++;
	}
}

int	inputing(t_data *data)
{
	while(!data->over)
	{
		if (data->cmds)
			del_cmd(data);
		// PROMPT ET GESTION DE LHISTORIQUE
		if (prompt(data) == -1)
			break ;
		//perror("prompt");
		// PASSER DE LA LIGNE A PLUSIEURS COMMANDE DIVISEES
		if (line_to_exe(data) == -1)
			perror("shell");
		pipe_loop(data);
		//aff_tkn(*data);
		//exe_cmds(&data);
		free(data->usr_input);
	}
	free_all(data);
	return (EXIT_SUCCESS);
}
