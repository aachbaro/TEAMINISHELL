/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:25:11 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/22 14:22:36 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * builtin env
 * display all the environnement variables
 */

int	built_env(t_envar *env)
{
	t_envar	*cpy;

	cpy = env;
	if (!cpy)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	display_env(env, 0);
	return (EXIT_SUCCESS);
}
