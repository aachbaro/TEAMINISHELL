/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:56:38 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/17 18:18:22 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_fds_redir(t_cmd cmd, t_redirtools *redir)
{
	redir->save_stdin = 0;
	redir->save_stdout = 0;
	redir->fd_in = 0;
	redir->fd_out = 0;
	if (get_fds_redir(cmd, redir) == -1)
		return (-1);
	if (redir->fd_in != -42)
	{
		dup2(redir->fd_in, STDIN_FILENO);
		close(redir->fd_in);
	}
	if (redir->fd_out != -42)
	{
		dup2(redir->fd_out, STDOUT_FILENO);
		close(redir->fd_out);
	}
	return (0);
}

void	restaure_fds_redir(t_redirtools *redir)
{
	dup2(redir->save_stdin, STDIN_FILENO);
	dup2(redir->save_stdout, STDOUT_FILENO);
	close(redir->save_stdout);
	close(redir->save_stdin);
}

int	get_fds_redir(t_cmd cmd, t_redirtools *redir)
{
	t_tkn	*cpy;

	cpy = cmd.tkn;
	redir->save_stdin = dup(STDIN_FILENO);
	redir->save_stdout = dup(STDOUT_FILENO);
	redir->fd_in = -42;
	redir->fd_out = -42;
	while (cpy)
	{
		if (cpy->type == TYPE_REDIN)
		{
			if (redir->fd_in != -42)
				close(redir->fd_in);
			redir->fd_in = init_redin(*cpy);
		}
		else if (cpy->type == TYPE_REDOUT || cpy->type == TYPE_APPEND)
		{
			if (redir->fd_out != -42)
				close(redir->fd_out);
			redir->fd_out = init_redout(*cpy);
		}
		if (redir->fd_in == -1 || redir->fd_out == -1)
			return (-1);
		cpy = cpy->next;
	}
	return (0);
}

int	init_redin(t_tkn tkn)
{
	int	fd;

	fd = open(tkn.content, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("shell : ", 2);
		ft_putstr_fd(tkn.content, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (fd);
}

int	init_redout(t_tkn tkn)
{
	int	fd;
	
	if (tkn.type == TYPE_REDOUT)
		fd = open(tkn.content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(tkn.content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_putstr_fd("shell: Error opening file\n", 2);
	return (fd);
}
