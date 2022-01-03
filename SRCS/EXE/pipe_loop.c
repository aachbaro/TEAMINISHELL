/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:34:17 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/22 16:53:31 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Code de test pour mettre les bons fd avec une loop sur les differnts pipe
void	pipe_loop(t_data *data)
{
	int	i;
	int	fds[2];
	int	old_fds[2];
	int	pid;

	i = 0;
	while (data->cmds[i].line)
	{
		if (data->cmds[i + 1].line)
			pipe(fds);
		pid = fork();
		if (pid == 0)
		{
			if (i)
			{
				dup2(old_fds[0], 0);
				close(old_fds[0]);
				close(old_fds[1]);
			}
			if (data->cmds[i + 1].line)
			{
				close(fds[0]);
				dup2(fds[1], 1);
				close(fds[1]);
			}
			if (is_builtin(data->cmds[i]))
				exe_builtin(data, i);
			else
				exe_path(data,i);
		}
		else
		{
			if (i)
			{
				close(old_fds[0]);
				close(old_fds[1]);
			}
			if (data->cmds[i + 1].line)
			{
				old_fds[0] = fds[0];
				old_fds[1] = fds[1];
			}
		}
		i++;
	}
	if (i > 1)
	{
		close(old_fds[0]);
		close(old_fds[1]);
	}
}
