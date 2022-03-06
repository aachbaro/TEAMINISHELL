/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:51:39 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/06 17:12:25 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_glob	g_g;

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	g_g.exit = 0;
	if (ac != 1 || !av)
	{
		ft_putstr_fd("minishell: wrong number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (shell_start(&data, envp))
	{
		ft_putstr_fd("minishell: Error initiating minishell\n", 2);
		return (EXIT_FAILURE);
	}
	return (inputing(&data));
}
