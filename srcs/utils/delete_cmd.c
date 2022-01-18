/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:42:29 by ababaei           #+#    #+#             */
/*   Updated: 2022/01/14 18:25:03 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * delete command
 * free all data on the precedent command to start working on a new one (?)
 */

void	del_cmd(t_data *data)
{
	int		i;

	i = 0;
	while (data->cmds[i].line)
	{
		free(data->cmds[i].line);
		free(data->cmds[i].path);
		del_tab(data->cmds[i].args);
		tkn_clear(&data->cmds[i].tkn);
		i++;
	}
	free(data->cmds);
}
