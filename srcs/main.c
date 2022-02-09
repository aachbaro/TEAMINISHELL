/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:51:39 by aachbaro          #+#    #+#             */
/*   Updated: 2022/02/08 16:50:55 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//sig_atomic_t	g_status;

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int i = 0;

	if (ac != 1 || !av)
		return (EXIT_FAILURE);
	while (envp[i])
		i++;
	shell_start(&data, envp);
	return (inputing(&data));
}
