/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:56:38 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/17 18:18:22 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exe_path(t_data *data, int cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(data->cmds[cmd].path, data->cmds[cmd].args,
					data->env) == -1)
			perror(data->cmds[cmd].path);
	}
}

int	is_builtin(t_cmd cmd)
{
	if (!ft_strncmp(cmd.line, "echo", 4) && ft_strlen(cmd.line) == 4)
		return (1);
	if (!ft_strncmp(cmd.line, "cd", 2) && ft_strlen(cmd.line) == 2)
		return (1);
	if (!ft_strncmp(cmd.line, "pwd", 3) && ft_strlen(cmd.line) == 3)
		return (1);
	if (!ft_strncmp(cmd.line, "export", 6) && ft_strlen(cmd.line) == 6)
		return (1);
	if (!ft_strncmp(cmd.line, "unset", 5) && ft_strlen(cmd.line) == 5)
		return (1);
	if (!ft_strncmp(cmd.line, "env", 3) && ft_strlen(cmd.line) == 3)
		return (1);
	if (!ft_strncmp(cmd.line, "exit", 4) && ft_strlen(cmd.line) == 4)
		return (1);
	return (0);
}

int	exe_builtin(t_data *data, int cmd)
{
	printf("%s : builtin en construssssion\n", data->cmds[cmd].tkn->content);
	return (0);
}

void	exe_cmds(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds[i].line)
	{
		// Check si la commande a exec est un builtin, l'execute
		if (is_builtin(data->cmds[i]))
			exe_builtin(data, i);
		// Sinon, lexecute avec execve
		else
			exe_path(data, i);
		i++;
	}
}
