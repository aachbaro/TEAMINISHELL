/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isexported.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:18:23 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/01 16:16:00 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * this function returns 0 if the var is not find in the environnement
 * and 1 if it does
 */

int	ft_isexported(t_envar *lst, char *name)
{
	int i;

	i = 0;
	if (!lst || !name)
		return (0);
	while(name[i] != '=')
		i++;	
	while (lst->next)
	{
		if (!ft_strncmp(lst->str, name, i))
			return (1);
		lst = lst->next;
	}
	return (0);
}
