/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:26:43 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/22 14:26:10 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * builtin cd
 * This function changes active directory
 */

int	built_cd(t_cmd cmd)
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
		return (EXIT_FAILURE);
	}
	if (chdir(cmd.tkn->next->content) == -1)
		perror("cd");
	return (EXIT_SUCCESS);
}
