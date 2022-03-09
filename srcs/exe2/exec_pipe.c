/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:04:37 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/09 21:01:16 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_pipe(t_data *data)
{
	int			i;
	t_pipetools	pipes;

	i = 0;
	pipes.save_stdout = dup(STDOUT_FILENO);
	pipes.save_stdin = dup(STDIN_FILENO);
	while (data->cmds && data->cmds[i].line)
	{
		exec_pipe2(&pipes, data, i);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGQUIT, &signal_handler);
		if (pipes.pid == -1)
		{
			perror("fork");
			return (-1);
		}
		else if (pipes.pid == 0)
			child_process(&pipes, data, i);
		else
			parent_process(&pipes, data, i);
		i++;
	}
	restaure_initial_fds(&pipes, i);
	return (0);
}

void	exec_pipe2(t_pipetools *pipes, t_data *data, int i)
{
	if (data->cmds[i + 1].line)
		pipe(pipes->fds);
	pipes->pid = fork();
	if (get_cmd_name(data->cmds[i])
		&& !ft_strncmp(get_cmd_name(data->cmds[i]),
			"./minishell", 11))
		g_g.status = 3;
	else
		g_g.status = 1;
}

void	child_process(t_pipetools *pipes, t_data *data, int i)
{
	child_process_init(pipes, data, i);
	if (init_fds_redir(data->cmds[i], &pipes->redir) == -1
		|| (!is_builtin(data->cmds[i])
			&& !data->cmds[i].path[0]))
		exit_child(data, pipes);
	if (is_builtin(data->cmds[i]))
	{
		exe_builtin(data, i);
		exit_child(data, pipes);
	}
	else
	{
		if (execve(data->cmds[i].path,
				data->cmds[i].args, lst_to_tab(data->env)) == -1)
		{
			perror(data->cmds[i].path);
			exit_child(data, pipes);
		}
	}
}

void	parent_process(t_pipetools *pipes, t_data *data, int i)
{
	if (i)
	{
		close(pipes->old_fds[0]);
		close(pipes->old_fds[1]);
	}
	if (data->cmds[i + 1].line)
	{
		pipes->old_fds[0] = pipes->fds[0];
		pipes->old_fds[1] = pipes->fds[1];
	}
	wait(&pipes->status);
	if (WIFEXITED(pipes->status))
		g_g.exit = WEXITSTATUS(pipes->status);
	restaure_fds_redir(&pipes->redir);
}

void	restaure_initial_fds(t_pipetools *pipes, int i)
{
	if (i > 1)
	{
		close(pipes->old_fds[0]);
		close(pipes->old_fds[1]);
	}
	dup2(pipes->save_stdin, STDIN_FILENO);
	dup2(pipes->save_stdout, STDOUT_FILENO);
	close(pipes->save_stdin);
	close(pipes->save_stdout);
}
