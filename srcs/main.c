/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:51:39 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/03 15:06:52 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_glob	g_g;
//sig_atomic_t	g_status;

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int i = 0;

	g_g.exit = 0;
	if (ac != 1 || !av)
		return (EXIT_FAILURE);
	while (envp[i])
		i++;
	shell_start(&data, envp);
	return (inputing(&data));
}
