/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:56:29 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/09 20:00:16 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	treat_hdinput2(char *input, t_data *data, t_dblquote_parser *pars)
{
	char	*var;

	var = ft_strndup(input + pars->i, pars->j - pars->i);
	if (!var)
		return (-1);
	if (pars->str)
		pars->tmp = ft_strjoin(pars->str, var);
	else
		pars->tmp = ft_strdup(var);
	free(var);
	if (pars->str)
		free(pars->str);
	if (input[pars->j] == '$')
	{
		pars->k = 1;
		var = var_name(input + pars->j - 1);
		if (!var)
			return (-1);
		pars->tmp2 = find_var(var, data->env, data->exit_status);
		pars->j += ft_strlen(var);
		free(var);
	}
	return (0);
}

void	heredoc_loop2(int fd, char *input, int quotes, t_data *data)
{
	char	*str;

	if (!quotes)
		str = treat_heredoc_input(input, data);
	else
		str = ft_strdup(input);
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	free(str);
}

int	init_heredoc2(char **name, t_pipetools *forks)
{
	forks->fds[0] = open(*name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (forks->fds[0] == -1)
	{
		free(*name);
		return (-1);
	}
	forks->pid = fork();
	if (forks->pid == -1)
	{
		close(forks->fds[0]);
		return (-1);
	}
	return (0);
}

void	init_redirtool(t_redirtools *redir)
{
	redir->save_stdin = dup(STDIN_FILENO);
	redir->save_stdout = dup(STDOUT_FILENO);
	redir->fd_in = -42;
	redir->fd_out = -42;
}
