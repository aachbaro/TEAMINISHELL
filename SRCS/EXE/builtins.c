/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:50:08 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/14 19:06:12 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	built_pwd(t_cmd cmd)
{
	char	buf[1000];

	if (cmd.tkn->next && cmd.tkn->next->type < 4)
		return (-1);
	getcwd(buf, 1000);
	ft_putstr_fd(buf, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

void	print_var(char *var, t_envar *env)
{
	t_envar	*cpy;

	cpy = env;
	while (cpy)
	{
		if (!ft_strncmp(var + 1, cpy->str, ft_strlen(var + 1))
				&& cpy->str[ft_strlen(var + 1)] == '=')
			break;
		cpy = cpy->next;
	}
	ft_putstr_fd(cpy->str + ft_strlen(var + 1) + 1, 1);
}

void	print_dblquote(char *content, t_envar *env)
{
	int	i;
	int	j;
	char	*var;

	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			j = i;
			while (content[j] && content[j] != ' ')
				j++;
			var = ft_strndup(content + i, j - i);
			print_var(var, env);
			free(var);
			i = j;
		}
		if (content[i])
			write(1, content + i, 1);
		i++;
	}
}

void	built_echo(t_cmd cmd, t_envar *env)
{
	t_tkn	*cpy;
	int	opt;

	cpy = cmd.tkn->next;
	opt = 0;
	while (cpy && cpy->type < 4 && !ft_strncmp(cpy->content, "-n", 2))
	{
		if (!ft_strncmp(cpy->content, "-n", 2))
			opt = 1;
		cpy = cpy->next;
	}
	while (cpy && cpy->type < 4)
	{
		if (cpy->type <= TYPE_DBLQUOTE)
			ft_putstr_fd(cpy->content, 1);
		else if (cpy->type == TYPE_VAR)
			print_var(cpy->content, env);
		cpy = cpy->next;
	}
	if (!opt)
		write(1, "\n", 1);
}

void	built_env(t_envar *env)
{
	t_envar	*cpy;

	cpy = env;
	while (cpy)
	{
		ft_putstr_fd(cpy->str, 1);
		write(1, "\n", 1);
		cpy = cpy->next;
	}
}
