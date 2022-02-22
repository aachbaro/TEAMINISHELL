/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:56:38 by aachbaro          #+#    #+#             */
/*   Updated: 2022/02/22 13:16:50 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exe_simple_cmd(t_data *data)
{
	t_redirtools	redir;
	if (init_fds_redir(data->cmds[0], &redir) == -1)
		return (-1);
	exe_builtin(data, 0);
	restaure_fds_redir(&redir);
	return (-1);
}

int	is_builtin(t_cmd cmd)
{
	if (!ft_strncmp(cmd.line, "echo", 4)
			&& ft_strlen(cmd.tkn->content) == 4)
		return (1);
	else if (!ft_strncmp(cmd.line, "cd", 2)
			&& ft_strlen(cmd.tkn->content) == 2)
		return (1);
	else if (!ft_strncmp(cmd.line, "pwd", 3)
			&& ft_strlen(cmd.tkn->content) == 3)
		return (1);
	else if (!ft_strncmp(cmd.line, "export", 6)
			&& ft_strlen(cmd.tkn->content) == 6)
		return (1);
	else if (!ft_strncmp(cmd.line, "unset", 5)
			&& ft_strlen(cmd.tkn->content) == 5)
		return (1);
	else if (!ft_strncmp(cmd.line, "env", 3)
			&& ft_strlen(cmd.tkn->content) == 3)
		return (1);
	else if (!ft_strncmp(cmd.line, "exit", 4)
			&& ft_strlen(cmd.tkn->content) == 4)
		return (1);
	return (0);
}

int	exe_builtin(t_data *data, int cmd)
{
	if (!ft_strncmp(data->cmds[cmd].line, "echo", 4))
		built_echo(data->cmds[cmd]);
	else if (!ft_strncmp(data->cmds[cmd].line, "pwd", 3))
		built_pwd(data->cmds[cmd]);
	else if (!ft_strncmp(data->cmds[cmd].line, "env", 3))
		built_env(data->env);
	else if (!ft_strncmp(data->cmds[cmd].line, "cd", 2))
		built_cd(data->cmds[cmd]);
	else if (!ft_strncmp(data->cmds[cmd].line, "export", 2))
		built_export(data->cmds[cmd], data);
	else if (!ft_strncmp(data->cmds[cmd].line, "exit", 4))
		data->over = 1;
	return (0);
}

