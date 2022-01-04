/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:51:39 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/22 16:49:56 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.cmds = NULL;
	data.old_line = NULL;
	data.over = 0;
	if (!ac || !av)
		return (0);
	data.env = init_env(env);
	while(!data.over)
	{
		if (data.cmds)
			del_cmd(&data);
		// PROMPT ET GESTION DE LHISTORIQUE
		if (prompt(&data) == -1)
			perror("prompt");
		// PASSER DE LA LIGNE A PLUSIEURS COMMANDE DIVISEES
		if (line_to_exe(&data) == -1)
			perror("shell");
		pipe_loop(&data);
		if (!ft_strncmp(data.line, "exit", 4))
			data.over = 1;
		free(data.line);
	}
	free_all(&data);
	return (0);
}
