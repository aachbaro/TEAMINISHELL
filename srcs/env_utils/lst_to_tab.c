/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:36:27 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/27 18:51:53 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * list to tab
 * This function transform a chained list into a string table
 * it takes the env in param and return a char **.
 */

char	**free_tab(char **tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (tab[i])
			free(tab[i]);
	}
	free(tab);
	return (NULL);
}

char	**lst_to_tab(t_envar *env)
{
	char **tab;
	int size;
	int i;
	
	size = env_size(env);
	i = 0;
	tab = calloc(size + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	tab[size] = NULL;
	while (tab[i])
	{
		tab[i] = ft_strdup(env->str);
		if (!tab[i])
			return (free_tab(tab,i));
		i++;
		env = env->next;
	}
	return (tab);
}
