/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:58:08 by ababaei           #+#    #+#             */
/*   Updated: 2022/01/14 18:24:25 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_splitted_cmd(t_data *data)
{
	int	i;
	t_tkn	*cpy;

	i = 0;
	while (data->cmds[i].line)
	{
		printf("\n\nCOMMAAAAAAAAAAAAAAAAAAANDE\n");
		printf("\ncmds[%d]->line = %s\n", i, data->cmds[i].line);
		cpy = data->cmds[i].tkn;
		while (cpy)
		{
			printf("\nTOKEN\ncontent = %s\ntype = %d\n", cpy->content, cpy->type);
			cpy = cpy->next;
		}
		i++;
	}
}

void	print_cmd_path_args(t_data *data)
{
	int	i;

	i = 0;
	printf("PATH = %s\n", data->cmds[0].path);
	while (data->cmds[0].args[i])
	{
		printf("arg [%d] = %s\n", i, data->cmds[0].args[i]);
		i++;
	}
}
