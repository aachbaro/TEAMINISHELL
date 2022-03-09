/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:51:59 by ababaei           #+#    #+#             */
/*   Updated: 2022/03/09 21:05:53 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * input.c
 * Here we have the main loop waiting for an input and then processing it
 * until the shell is over.
 * check readme for g_status values meaning.
 * this function is called in the return of main.c
 */

int	inputing(t_data *data)
{
	int	ret;

	while (!data->over)
	{
		signal(SIGQUIT, SIG_IGN);
		g_g.status = 0;
		g_g.exit = 0;
		if (data->cmds)
			del_cmd(data);
		if (prompt(data) == -1)
			break ;
		ret = input_to_exe(data);
		if (data->cmds && data->cmds->line && !ret)
		{
			if (data->cmds[1].line == NULL && is_builtin(data->cmds[0]))
				exe_simple_cmd(data);
			else
				exec_pipe(data);
		}
		data->exit_status = g_g.exit;
		free(data->usr_input);
	}
	return (free_all(data), g_g.exit);
}

int	prompt(t_data *data)
{
	data->usr_input = readline("8=o-- ");
	if (!data->usr_input)
	{
		ft_putchar_fd('\n', 1);
		return (-1);
	}
	if (!data->prev_input || (ft_strncmp(data->usr_input, data->prev_input,
				ft_strlen(data->usr_input))
			|| ft_strlen(data->prev_input) != ft_strlen(data->usr_input)))
		add_history(data->usr_input);
	free(data->prev_input);
	data->prev_input = ft_strdup(data->usr_input);
	if (!data->prev_input)
		return (-1);
	return (0);
}
