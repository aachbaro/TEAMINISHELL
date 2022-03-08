/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:21:01 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/07 21:07:40 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * shell starter
 * assign starter values, create environnement, and config signal handlers
 */

int	shell_start(t_data *data, char **env)
{
	t_envar	*tmp;
	char	*shlvl;
	char	*envstr;

	data->cmds = NULL;
	data->prev_input = NULL;
	data->over = 0;
	data->exit_status = 0;
	data->heredoc_id = 0;
	data->env = init_env(env);
	if (!data->env)
		return (EXIT_FAILURE);
	data->in_env = lst_to_tab(data->env);
	tmp = find_envar(data->env, "SHLVL");
	shlvl = ft_itoa(ft_atoi(tmp->value) + 1);
	envstr = ft_strjoin("SHLVL=", shlvl);
	if (!envstr || !shlvl)
		return (EXIT_FAILURE);
	change_env(&tmp, envstr);
	free(shlvl);
	free(envstr);
	sig_config();
	return (EXIT_SUCCESS);
}
