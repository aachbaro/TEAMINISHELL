/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:44:52 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/06 17:45:02 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * free environnement variable
 * free memory of an envar node (str, key, value)
 */

void	free_envar(t_envar *var)
{
	free(var->str);
	free(var->key);
	free(var->value);
	free(var);
}
