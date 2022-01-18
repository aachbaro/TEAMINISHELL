/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:21:01 by ababaei           #+#    #+#             */
/*   Updated: 2022/01/14 18:27:56 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * shell starter
 * assign starter values, create environnement, and config signal handlers
 */

void	shell_start(t_data *data, char **env)
{
	data->cmds = NULL;
	data->old_line = NULL;
	data->over = 0;
	data->in_env = env;
	data->env = init_env(env);
	sig_config();
}
