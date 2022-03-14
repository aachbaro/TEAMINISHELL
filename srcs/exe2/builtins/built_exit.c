/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:04:19 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/08 23:32:12 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	built_exit(t_cmd cmd, t_data *data)
{
	t_tkn	*cpy;
	int		i;

	cpy = cmd.tkn;
	i = 0;
	while (cpy->next)
	{
		i++;
		cpy = cpy->next;
	}
	if (i > 2)
	{
		ft_putstr_fd("Shell: exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (i > 1 && !ft_strisdigit(cpy->content))
	{
		ft_putstr_fd("Shell: exit: numeric argument required\n", 2);
		return (EXIT_FAILURE);
	}
	if (!cpy)
		i = 0;
	else
		i = ft_atoi(cpy->content);
	return (rl_clear_history(), data->over = 1, i);
}