/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:28:31 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/22 11:59:18 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * Let you export a variable in your environnement
 

void	change_env(t_envar *env, char *from, char *to)
{
	
}*/

void	built_export(t_cmd cmd, t_envar *env)
{
	t_tkn	*cpy;
		
	printf("TOTO\n");
	cpy = cmd.tkn->next;
	if (cpy->next || cpy->type > 3)
		return ; // msg erreur type export [name[=value]...]
	if (ft_isexported(env, cpy->content))
		printf("CACA\n");
}
