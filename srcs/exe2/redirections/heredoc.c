/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:57:22 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/09 20:05:36 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * here document
 * starts at init_heredoc which is called in set_redirections.c
 */

int	init_heredoc(t_tkn *tkn, int heredoc_id, t_data *data)
{
	t_pipetools	fork;
	char		*heredoc_name;

	heredoc_name = filename_generator(heredoc_id);
	if (!heredoc_name || init_heredoc2(&heredoc_name, &fork) == -1)
		return (-1);
	if (fork.pid == 0)
	{
		g_g.status = 2;
		free(heredoc_name);
		heredoc_loop(fork.fds[0], tkn->content, data, tkn->quotes);
	}
	wait(&fork.status);
	if (g_g.exit == 130)
	{
		unlink(heredoc_name);
		close(fork.fds[0]);
		free(heredoc_name);
		return (130);
	}
	close(fork.fds[0]);
	free(tkn->content);
	tkn->content = heredoc_name;
	return (0);
}

void	heredoc_loop(int fd, char *delim, t_data *data, int quotes)
{
	int		end;
	char	*input;

	end = 0;
	while (!end && !g_g.exit)
	{
		input = readline("heredoc > ");
		if (!input)
		{
			ft_putstr_fd("here-doc delimited by end-of-file\n", 1);
			break ;
		}
		if (ft_strncmp(input, delim, ft_strlen(input) + 1) == 0)
			end = 1;
		else
			heredoc_loop2(fd, input, quotes, data);
		free(input);
	}
	close(fd);
	free_all(data);
	exit(0);
}

char	*filename_generator(int heredoc_id)
{
	char	*str;
	char	*str2;
	char	*ret;

	str = ft_strdup(".heredoc_");
	if (!str)
		return (NULL);
	str2 = ft_itoa(heredoc_id);
	if (!str2)
	{
		free(str);
		return (NULL);
	}
	ret = ft_strjoin(str, str2);
	free(str);
	free(str2);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*treat_heredoc_input(char *input, t_data *data)
{
	t_dblquote_parser	pars;

	pars.i = 0;
	pars.str = NULL;
	if (input[0] == 0)
		return (ft_strdup(""));
	while (input[pars.i])
	{
		pars.j = pars.i;
		while (input[pars.j] && input[pars.j] != '$')
			pars.j++;
		pars.k = 0;
		if (treat_hdinput2(input, data, &pars))
			return (NULL);
		if (input[pars.j] != '$' && !pars.k)
			pars.tmp2 = ft_strdup("");
		if (!pars.tmp2)
			return (NULL);
		pars.str = ft_strjoin(pars.tmp, pars.tmp2);
		free(pars.tmp);
		free(pars.tmp2);
		pars.i = pars.j;
	}
	return (pars.str);
}

char	*var_name(char *str)
{
	int		i;
	char	*var;

	i = 2;
	while (str[i] && !ft_strchr(" <>$\"'", str[i]))
		i++;
	var = ft_strndup(str + 1, i - 1);
	if (!var)
		return (NULL);
	return (var);
}
