/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:51:39 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/03 15:30:29 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_glob	g_g;

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	g_g.exit = 0;
	if (ac != 1 || !av)
		return (EXIT_FAILURE);
	shell_start(&data, envp);
	return (inputing(&data));
}
