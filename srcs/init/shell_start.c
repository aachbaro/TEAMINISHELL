/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:21:01 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/02 14:17:46 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * shell starter
 * assign starter values, create environnement, and config signal handlers
 */

void	shell_start(t_data *data, char **env)
{
	t_envar *tmp;
	char *shlvl;
	char *envstr;

	data->cmds = NULL;
	data->prev_input = NULL;
	data->over = 0;
	data->env = init_env(env);
	data->in_env = lst_to_tab(data->env);
	tmp = find_envar(data->env, "SHLVL");
	shlvl = ft_itoa(ft_atoi(tmp->value) + 1);
	envstr = ft_strjoin("SHLVL=", shlvl);
	change_env(&tmp, envstr);
	free(shlvl);
	free(envstr);
	sig_config();
}
