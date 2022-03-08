/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:44:49 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/08 14:23:54 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * free all stuff that has been allocated
 */

//Added assignation to NULL when freed to prevent from getting error

void	free_env_tab(char **env)
{
	int i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			free(env[i]);
			env[i] = NULL;
			i++;
		}
		free(env);
		env = NULL;
	}
}

void	free_all(t_data *data)
{
	t_envar	*cpy;

	if (data->prev_input)
	{
		free(data->prev_input);
		data->prev_input = NULL;
	}
	if (data->usr_input && data->cmds->line)
		del_cmd(data);
	while (data->env)
	{
		cpy = data->env->next;
		free_envar(data->env);
		data->env = cpy;
	}
	free_env_tab(data->in_env);
}
