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

void	built_echo(t_cmd cmd)
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
		if (cpy->type <= TYPE_DBLQUOTE || cpy->type == TYPE_VAR)
			ft_putstr_fd(cpy->content, 1);
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

void	built_cd(t_cmd cmd)
{
	t_tkn	*cpy;
	int	i;

	cpy = cmd.tkn;
	i = 0;
	while (cpy && cpy->type < TYPE_QUOTE)
	{
		i++;
		cpy = cpy->next;
	}
	if (i != 2)
	{
		ft_putstr_fd("Shell: cd: Wrong number of arguments\n", 1);
		return ;
	}
	if (chdir(cmd.tkn->next->content) == -1)
		perror("cd");
}
