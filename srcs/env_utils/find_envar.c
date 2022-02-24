/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_envar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:18:23 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/24 17:25:59 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * this function returns a ptr on the env variable if its founnd in environnement,
 * and NULL if not.
 */

t_envar	*find_envar(t_envar *lst, char *name)
{
	int i;

	i = 0;
	if (!lst || !name)
		return (NULL);
	while(name[i] != '=' && name[i])
		i++;
	while (lst)
	{
		if (!ft_strncmp(lst->str, name, i))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
