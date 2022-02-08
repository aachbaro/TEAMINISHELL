/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:44:49 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/08 16:48:13 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * free all stuff that has been allocated
 */

void	free_all(t_data *data)
{
	t_envar *tmp;

	if (data->prev_input)
		free(data->prev_input);
	if (data->usr_input && data->cmds->line)
		del_cmd(data);
	while (data->env->next)
	{
		tmp = data->env->next;
		free_envar(data->env);
		data->env = tmp;
	}
	free_envar(data->env);
}
