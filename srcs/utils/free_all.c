/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:44:49 by ababaei           #+#    #+#             */
/*   Updated: 2022/01/14 18:26:43 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * free all stuff that has been allocated
 */

void	free_all(t_data *data)
{
	if (data->prev_input)
		free(data->prev_input);
	if (data->usr_input && data->cmds->line)
		del_cmd(data);
}
