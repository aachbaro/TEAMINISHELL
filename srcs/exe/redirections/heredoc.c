/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:57:22 by aachbaro          #+#    #+#             */
/*   Updated: 2022/02/24 17:01:09 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	init_heredoc(t_tkn *tkn, int heredoc_id, t_envar *env)
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
	printf("%d\n", tkn->quotes);
	if (heredoc_loop(fd, tkn->content, env, tkn->quotes) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	free(tkn->content);
	tkn->content = heredoc_name;
	return (0);
}

int	heredoc_loop(int fd, char *delim, t_envar *env, int quotes)
{
	int	end;
	char	*input;
	char	*str;

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
			if (!quotes)
				str = treat_heredoc_input(input, env);
			else
				str = ft_strdup(input);
			ft_putstr_fd(str, fd);
			ft_putchar_fd('\n', fd);
			free(str);
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

char	*treat_heredoc_input(char *input, t_envar *env)
{
	t_dblquote_parser	pars;
	char			*var;

	pars.i = 0;
	pars.str = NULL;
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
			pars.tmp2 = find_var(var, env);
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
	int	i;
	char	*var;

	i = 2;
	while (str[i] && !ft_strchr(" <>$\"'", str[i]))
		i++;
	var = ft_strndup(str + 1, i - 1);
	if (!var)
		return (NULL);
	return (var);
}
