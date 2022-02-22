/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:51:59 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/22 14:49:15 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (prompt(data) == -1)
			break ;
		if (input_to_exe(data) == -1)
			perror("shell");
		if (data->cmds->line)
		{
			if (data->cmds[1].line == NULL 
					&& is_builtin(data->cmds[0]))
				exe_simple_cmd(data);
			else
				exec_pipe(data);
		}
		free(data->usr_input);
	}
	free_all(data);
	return (EXIT_SUCCESS);
}

int	prompt(t_data *data)
{
	// On recupere la commande entree par l'utilsateur
	data->usr_input = readline("~>");
	// Check si on doit rentrer la ligen dans lhistorique
	//data->env = data->env->next;
	printf("DEBUG::%s::\n", data->usr_input);
	if (!data->usr_input)
		return (-1);
	if (!data->prev_input || (ft_strncmp(data->usr_input, data->prev_input,
		ft_strlen(data->usr_input)) || ft_strlen(data->prev_input)
			!= ft_strlen(data->usr_input)))
		add_history(data->usr_input);
	free(data->prev_input);
	data->prev_input = ft_strdup(data->usr_input);
	if (!data->prev_input)
		return (-1);
	return (0);
}
