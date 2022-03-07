/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:26:43 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/07 12:56:05 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * builtin cd
 * This function changes active directory
 */

int	built_cd(t_cmd cmd, t_data *data)
{
	t_tkn	*cpy;
	t_envar	*pwd;
	t_envar	*oldpwd;
	int		i;

	cpy = cmd.tkn;
	i = 0;
	pwd = find_envar(data->env, "PWD");
	oldpwd = find_envar(data->env, "OLDPWD");
	while (cpy && cpy->type < TYPE_QUOTE)
	{
		i++;
		cpy = cpy->next;
	}
	if (i != 2)
	{
		ft_putstr_fd("Shell: cd: Wrong number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	change_env(&oldpwd, ft_strjoin("OLDPWD=", getcwd(NULL, 10000)));
	if (chdir(cmd.tkn->next->content) == -1)
		perror("cd");
	change_env(&pwd, ft_strjoin("PWD=", (getcwd(NULL, 10000))));
	return (EXIT_SUCCESS);
}
