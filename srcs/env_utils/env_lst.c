/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:54:20 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/24 16:51:24 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

/*
 * environnement chained list tools
 * We have here several function to create, delete and add to the env chained list
 */

t_envar *fill_envar(t_envar **lst, char *str)
{
	char *key;
	char *value;
	unsigned int i;

	i = 0;
	(*lst)->str = ft_strdup(str);
	if (!(*lst)->str)
		return (NULL);
	while (str[i] != '=')
		i++;
	key = ft_strndup(str, i);
	if (!key)
		return (NULL);
	value = ft_strdup(str + i + 1);
	if (!value)
		return (NULL);
	(*lst)->key = key;
	(*lst)->value = value;
	return (*lst);
}

t_envar	*add_env(t_envar **lst, char *str)
{
	t_envar	*tmp;
	t_envar *save;

	save = *lst;
	tmp = malloc(sizeof(t_envar));
	if (!tmp)
		return (NULL);
	fill_envar(&tmp, str);
	if (!tmp)
		return (NULL);
	tmp->next = NULL;
	if (*lst == NULL)
	{
		*lst = tmp;
		return (*lst);
	}
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = tmp;
	*lst = save;
	return (*lst);
}

t_envar	*init_env(char **env)
{
	t_envar	*envlst;
	int i;

	i = 0;
	envlst = NULL;
	while (env[i])
	{
		add_env(&envlst, env[i]);
		i++;
	}	
	return (envlst);
}

/* USE REMOVE_VAR INSTEAD
int	delete_env(t_envar **lst, char *name)
{
	t_envar *tmp;

	while (ft_strncmp((*lst)->str, name, ft_strlen(name)))
	{
		tmp = *lst;
		*lst = (*lst)->next;
	}
	if (!(*lst) || *((*lst)->str + 1) != '=')
		return (EXIT_FAILURE);
	if ((*lst)->str)
		free((*lst)->str);
	tmp->next = (*lst)->next;
	free(*lst);
	*lst = tmp;
	return (EXIT_SUCCESS);
}*/

int	remove_var(t_envar **env, char *key)
{
	t_envar *curr;
	t_envar *prev;

	curr = *env;
	prev = *env;
	while (*env)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			prev->next = curr->next;
			free_envar(curr);
			return (EXIT_SUCCESS);
		}
		prev = curr;
		curr = curr->next;
	}
	return (EXIT_FAILURE);
}
