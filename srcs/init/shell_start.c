/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:21:01 by ababaei           #+#    #+#             */
/*   Updated: 2022/02/27 18:53:01 by ababaei          ###   ########.fr       */
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

	data->cmds = NULL;
	data->prev_input = NULL;
	data->over = 0;
	data->in_env = env;
	data->env = init_env(env);
	tmp = find_envar(data->env, "SHLVL");
	shlvl = ft_itoa(ft_atoi(tmp->value) + 1);
	change_env(&tmp, ft_strjoin("SHLVL=", shlvl));
	free(shlvl);
	sig_config();
}
