/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:57:22 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/07 14:09:27 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * here document
 * starts at init_heredoc which is called in set_redirections.c
 */

int	init_heredoc(t_tkn *tkn, int heredoc_id, t_data *data)
{
	int			fd;
	t_pipetools	forktool;
	char		*heredoc_name;

	heredoc_name = filename_generator(heredoc_id);
	if (!heredoc_name)
		return (-1);
	fd = open(heredoc_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		free(heredoc_name);
		return (-1);
	}
	forktool.pid = fork();
	if (forktool.pid == -1)
	{
		close(fd);
		return (-1);
	}
	else if (forktool.pid == 0)
	{
		g_g.status = 2;
		heredoc_loop(fd, tkn->content, data, tkn->quotes);
	}
	else
	{
		wait(&forktool.status);
		if (g_g.exit == 130)
		{
			unlink(heredoc_name);
			close(fd);
			return (130);
		}
		else if (forktool.status == 139)
			ft_putstr_fd("warning: here-document delimited by end-of-file\n", 1);
	}
	close(fd);
	free(tkn->content);
	tkn->content = heredoc_name;
	return (0);
}

void	heredoc_loop(int fd, char *delim, t_data *data, int quotes)
{
	int		end;
	char	*input;
	char	*str;

	end = 0;
	while (!end)
	{
		input = readline("heredoc > ");
		if (*input == EOF)
			break ;
		if (ft_strncmp(input, delim, ft_strlen(input) + 1) == 0)
			end = 1;
		else
		{
			if (!quotes)
				str = treat_heredoc_input(input, data);
			else
				str = ft_strdup(input);
			ft_putstr_fd(str, fd);
			ft_putchar_fd('\n', fd);
			free(str);
		}
		free(input);
	}
	close(fd);
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
	char				*var;

	pars.i = 0;
	pars.str = NULL;
	if (input[0] == 0)
		return (ft_strdup(""));
	while (input[pars.i])
	{
		pars.j = pars.i;
		while (input[pars.j] && input[pars.j] != '$')
			pars.j++;
		var = ft_strndup(input + pars.i, pars.j - pars.i);
		if (!var)
			return (NULL);
		if (pars.str)
			pars.tmp = ft_strjoin(pars.str, var);
		else
			pars.tmp = ft_strdup(var);
		free(var);
		if (pars.str)
			free(pars.str);
		if (input[pars.j] == '$')
		{
			var = var_name(input + pars.j - 1);
			if (!var)
				return (NULL);
			pars.tmp2 = find_var(var, data->env, data->exit_status);
			pars.j += ft_strlen(var);
			free(var);
			if (!pars.tmp2)
				return (NULL);
		}
		else
		{
			pars.tmp2 = ft_strdup("");
			if (!pars.tmp2)
				return (NULL);
		}
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
