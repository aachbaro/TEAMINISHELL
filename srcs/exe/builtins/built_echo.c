/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:23:21 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/01 11:25:40 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* 
 * builtin echo
 * display a line of text
 */

int	check_opt(char *content)
{
	int	i;

	i = 1;
	if (ft_strncmp(content, "-n", 2))
		return (0);
	while (content[i])
	{
		if (content[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	built_echo(t_cmd cmd)
{
	t_tkn	*cpy;
	int	opt;

	cpy = cmd.tkn->next;
	opt = 0;
	while (cpy && cpy->type < 4 && check_opt(cpy->content))
	{
		if (check_opt(cpy->content))
			opt = 1;
		cpy = cpy->next;
	}
	while (cpy)
	{
		if (cpy->type <= TYPE_VAR)
			ft_putstr_fd(cpy->content, 1);
		ft_putchar_fd(' ', 1);
		cpy = cpy->next;
	}
	if (!opt)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
