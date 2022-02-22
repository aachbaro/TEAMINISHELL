/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:28:31 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/22 16:23:40 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * Let you export a variable in your environnement
 */

int		check_key(char *str)
{
	int i;
	
	i = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (0); 
	while (str[i] == '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

t_envar	*change_env(t_envar **envar, char *to)
{
	int i;

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

int	built_export(t_cmd cmd, t_data *data)
{
	t_tkn	*cpy;
	t_envar *tmp;

	if (cmd.tkn->next == NULL)	
		display_env(data->env, 1); // here print env with declare -x
	cpy = cmd.tkn->next;
	if (cpy && cpy->type > 3)
	{
		ft_putstr_fd("minishel: export: syntax error\n", 2);
		return (EXIT_FAILURE); // msg erreur type export [name[=value]...]
	}
	while (cpy)
	{
		if (!check_key(cpy->content))
		{
			printf("ID [%s] non valide\n", cpy->content);
			cpy = cpy->next;
			continue ;
		}
		tmp = find_envar(data->env, cpy->content);
		if (tmp)
			change_env(&tmp, cpy->content);
		else
			add_env(&(data->env), cpy->content);
		cpy = cpy->next;
	}
	return (EXIT_SUCCESS);
}
