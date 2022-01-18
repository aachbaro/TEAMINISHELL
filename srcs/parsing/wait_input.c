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

/*
 * input.c
 * Here we have the main loop waiting for an input and then processing it
 * until the shell is over.
 * check readme for g_status values meaning.
 * this function is called in the return of main.c
 */

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
		//exe_cmds(&data);
		free(data->line);
	}
	free_all(data);
	return (EXIT_SUCCESS);
}
