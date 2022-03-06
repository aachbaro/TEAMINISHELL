/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:04:19 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/06 15:51:37 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	built_exit(t_cmd cmd, t_data *data)
{
	t_tkn	*cpy;
	int	i;
	int ret;

	cpy = cmd.tkn;
	i = 0;
	while (cpy->next)
	{
		i++;
		cpy = cpy->next;
	}
	if (i > 1)
	{
		ft_putstr_fd("Shell: exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (!ft_strisdigit(cpy->content))
	{
		ft_putstr_fd("Shell: exit: numeric argument required\n", 2);
		return (EXIT_FAILURE);
	}
	if (!cpy)
		ret = 0;
	else
		ret = ft_atoi(cpy->content);
	return (rl_clear_history(), data->over = 1, ret);
}
