/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:00:40 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/01 20:43:41 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Display the environnement variables
 * either with env or export builtins with the flag
 * flag 0 -> env builtin
 * flag 1 -> export builtin, put "declare -x " before every var
 */

void	display_env(t_envar *env, int flag)
{
	while (env)
	{
		if (flag)
			
	}
}
