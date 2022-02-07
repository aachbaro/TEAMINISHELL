/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:54:20 by ababaei           #+#    #+#             */
/*   Updated: 2022/01/20 16:17:45 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

/*
 * environnement chained list tools
 * We have here several function to create, delete and add to the env chained list
 */

t_envar *new_env(char **env)
{
	t_envar *lst;

	lst = malloc(sizeof(t_envar));
	if (lst == NULL)
		return (NULL);
	lst->str = ft_strdup(env[0]);
	lst->next = NULL;
	return (lst);
}

t_envar	*add_env(t_envar **lst, char *str)
{
	t_envar	*tmp;
	t_envar *save;

	save = *lst;
	tmp = malloc(sizeof(t_envar));
	tmp->str = ft_strdup(str);
	if (!tmp || !tmp->str)
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
	envlst = new_env(env);
	if (envlst == NULL)
		return (NULL);
	while (env[++i])
		add_env(&envlst, env[i]);
	return (envlst);
}

void	delete_env(t_envar **lst, char *name)
{
	t_envar *tmp;

	while (ft_strncmp((*lst)->str, name, ft_strlen(name)))
	{
		tmp = *lst;
		*lst = (*lst)->next;
	}
	if (!(*lst) || *((*lst)->str + 1) != '=')
		return ;
	if ((*lst)->str)
		free((*lst)->str);
	tmp->next = (*lst)->next;
	free(*lst);
	*lst = tmp;
}
