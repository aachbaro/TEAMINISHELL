/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:51:39 by aachbaro          #+#    #+#             */
/*   Updated: 2022/01/18 11:50:07 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//sig_atomic_t	g_status;

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 1 || !av)
		return (EXIT_FAILURE);
	shell_start(&data, envp);
	return (inputing(&data));
}
