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

char	*find_var(char *var, t_envar *env)
{
	t_envar	*cpy;
	char	*ret;

	cpy = env;
	while (cpy)
	{
		if (!ft_strncmp(var + 1, cpy->str, ft_strlen(var + 1))
				&& cpy->str[ft_strlen(var + 1)] == '=')
			break;
		cpy = cpy->next;
	}
	if (cpy)
	{
		ret = ft_strdup(cpy->str + ft_strlen(var + 1) + 1);
		if (!ret)
			return (NULL);
	}
	else
		ret = ft_strdup("");
	return (ret);
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

