/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:21:29 by ababaei           #+#    #+#             */
/*   Updated: 2022/01/14 18:27:42 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * builtin pwd
 * function that we had to recode
 * it tells the directory where we are
 */

int	built_pwd(t_cmd cmd)
{
	char	buf[1000];

	if (cmd.tkn->next && cmd.tkn->next->type < 4)
		return (-1);
	getcwd(buf, 1000);
	ft_putstr_fd(buf, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
