/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:25:11 by ababaei           #+#    #+#             */
/*   Updated: 2022/01/14 18:27:32 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * builtin env
 * display all the environnement variables
 */

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
