/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:54:20 by ababaei           #+#    #+#             */
/*   Updated: 2022/01/18 11:11:02 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

/*
 * environnement chained list tools
 * We have here several function to create, delete and add to the env chained list
 */

t_envar *fill_envar(t_envar *lst, char *str)
{
	char *key;
	char *value;
	unsigned int i;

	i = 0;
	lst->str = ft_strdup(str);
	if (!lst->str)
		return (NULL);
	while (str[i] != '=')
		i++;
	key = ft_strndup(str, i);
	if (!key)
		return (NULL);
	value = ft_strdup(str + i + 1);
	if (!value)
		return (NULL);
	lst->key = key;
	lst->value = value;
	return (lst);
}

t_envar	*add_env(t_envar **lst, char *str)
{
	t_envar	*tmp;
	t_envar *save;

	save = *lst;
	tmp = malloc(sizeof(t_envar));
	if (!tmp)
		return (NULL);
	tmp = fill_envar(tmp, str);
	if (!tmp)
		return (NULL);
	tmp->next = NULL;
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

	i = -1;
	envlst = malloc(sizeof(t_envar));
	if (!envlst)
		return (NULL);
	envlst = fill_envar(envlst, env[0]);
	if (!envlst)
		return (NULL);
	while (env[++i])
		add_env(&envlst, env[i]);
	return (envlst);
}
