/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:44:49 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/06 17:28:58 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * free all stuff that has been allocated
 */

void	free_all(t_data *data)
{
	t_envar	*cpy;
	int i;

	i = 0;
	if (data->prev_input)
		free(data->prev_input);
	if (data->usr_input && data->cmds->line)
		del_cmd(data);
	while (data->env)
	{
		cpy = data->env->next;
		free_envar(data->env);
		data->env = cpy;
	}
	while (data->in_env[i])
	{
		free(data->in_env[i]);
		i++;
	}
	free(data->in_env);
}
