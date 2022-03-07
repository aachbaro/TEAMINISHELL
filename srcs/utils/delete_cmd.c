/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:42:29 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/07 15:12:48 by ababaei          ###   ########.fr       */
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
	if (!data->cmds)
		return ;
	while (data->cmds[i].line)
	{
		if (data->cmds[i].line)
			free(data->cmds[i].line);
		if (data->cmds[i].line && data->cmds[i].path)
			free(data->cmds[i].path);
		if (data->cmds[i].args)
			del_tab(data->cmds[i].args);
		tkn_clear(&data->cmds[i].tkn);
		i++;
	}
	free(data->cmds);
	data->cmds = NULL; //rajouter pour eviter un heap use after free, mais segv mtn
}
