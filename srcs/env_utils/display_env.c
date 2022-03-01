/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:00:40 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/24 16:56:34 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Display the environnement variables
 * either with env or export builtins with the flag
 * flag 0 -> env builtin
 * flag 1 -> export builtin, put "declare -x " before every var
 */

void	display_env(t_envar *env, int flag)
{
	t_envar *cpy;

	cpy = env;
	while (cpy)
	{
		if (flag)
			ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(cpy->str, 1);
		if (flag && *(ft_strchr(cpy->str, '=') + 1) == '\0')
			write(1, "''", 2);
		write(1, "\n", 1);
		cpy = cpy->next;
	}
}
