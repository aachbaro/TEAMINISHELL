/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:23:21 by ababaei           #+#    #+#             */
/*   Updated: 2022/01/14 18:27:21 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* 
 * builtin echo
 * display a line of text
 */

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
