/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:34:17 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/22 16:53:31 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_heredoc(t_tkn *tkn, int heredoc_id)
{
	int	fd;
	char	*heredoc_name;

	heredoc_name = filename_generator(heredoc_id);
	if (!heredoc_name)
		return (-1);
	fd = open(heredoc_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		free(heredoc_name);
		return (-1);
	}
	if (heredoc_loop(fd, tkn->content) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	free(tkn->content);
	tkn->content = heredoc_name;
	return (0);
}

int	heredoc_loop(int fd, char *delim)
{
	int	end;
	char	*input;

	end = 0;
	while (!end)
	{
		input = readline("heredoc > ");
		if (!input)
			return (-1);
		if (ft_strncmp(input, delim, ft_strlen(input) + 1) == 0)
			end = 1;
		else
		{
			ft_putstr_fd(input, fd);
			ft_putchar_fd('\n', fd);
		}
		free(input);
	}
	return (0);
}

char	*filename_generator(int	heredoc_id)
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
