/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:35:53 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/14 23:09:14 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_envar	*change_env(t_envar **envar, char *to)
{
	int	i;

	i = 0;
	while (to[i] != '=')
		i++;
	free((*envar)->str);
	free((*envar)->value);
	(*envar)->str = ft_strdup(to);
	(*envar)->value = ft_strdup(to + i + 1);
	if ((*envar)->value == NULL)
		return (NULL);
	return (*envar);
}
