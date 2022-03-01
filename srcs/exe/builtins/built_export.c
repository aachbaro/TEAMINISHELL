/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:28:31 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/24 20:42:49 by ababaei          ###   ########.fr       */
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
	while (str[i])
	{
		if (i > 0 && str[i] == '=')
			return (1);
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	handle_var(t_envar **env, t_envar *var, t_tkn *cpy)
{
	char *tmp;

	tmp = NULL;
	var = find_envar(*(env), cpy->content);
	if (!ft_strchr(cpy->content, '='))
	{
		tmp = ft_strjoin(cpy->content, "=");
		add_env(env, tmp);
		return ;
	}
	if (var)
		change_env(&var, cpy->content);
	else
		add_env(env, cpy->content);
}

int	built_export(t_cmd cmd, t_data *data)
{
	t_tkn	*cpy;
	t_envar *tmp;

	tmp = NULL;
	if (cmd.tkn->next == NULL)	
		display_env(data->env, 1); // here print env with declare -x
	cpy = cmd.tkn->next;
	if (cpy && cpy->type > 3)
	{
		ft_putstr_fd("minishell: export: syntax error\n", 2);
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
		handle_var(&(data->env), tmp, cpy);
		cpy = cpy->next;
	}
	return (EXIT_SUCCESS);
}
