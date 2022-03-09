/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:26:39 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/09 21:05:55 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_process_init(t_pipetools *pipes, t_data *data, int i)
{
	if (i)
	{
		dup2(pipes->old_fds[0], 0);
		close(pipes->old_fds[0]);
		close(pipes->old_fds[1]);
	}
	if (data->cmds[i + 1].line)
	{
		close(pipes->fds[0]);
		dup2(pipes->fds[1], 1);
		close(pipes->fds[1]);
	}
	else
	{
		dup2(pipes->save_stdout, STDOUT_FILENO);
		close(pipes->save_stdout);
	}
}
