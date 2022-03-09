/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:56:38 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/06 15:25:51 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exe_simple_cmd(t_data *data)
{
	t_redirtools	redir;

	if (init_fds_redir(data->cmds[0], &redir) == -1)
		return (-1);
	g_g.exit = exe_builtin(data, 0);
	restaure_fds_redir(&redir);
	return (0);
}

int	is_builtin(t_cmd cmd)
{
	char	*name;

	name = get_cmd_name(cmd);
	if (!name)
		return (0);
	if (!ft_strncmp(name, "echo", 4) && ft_strlen(name) == 4)
		return (1);
	else if (!ft_strncmp(name, "cd", 2) && ft_strlen(name) == 2)
		return (1);
	else if (!ft_strncmp(name, "pwd", 3) && ft_strlen(name) == 3)
		return (1);
	else if (!ft_strncmp(name, "export", 6) && ft_strlen(name) == 6)
		return (1);
	else if (!ft_strncmp(name, "unset", 5) && ft_strlen(name) == 5)
		return (1);
	else if (!ft_strncmp(name, "env", 3) && ft_strlen(name) == 3)
		return (1);
	else if (!ft_strncmp(name, "exit", 4) && ft_strlen(name) == 4)
		return (1);
	return (0);
}

int	exe_builtin(t_data *data, int cmd)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(get_cmd_name(data->cmds[cmd]), "echo", 4))
		ret = built_echo(data->cmds[cmd]);
	else if (!ft_strncmp(get_cmd_name(data->cmds[cmd]), "pwd", 3))
		ret = built_pwd(data->cmds[cmd]);
	else if (!ft_strncmp(get_cmd_name(data->cmds[cmd]), "env", 3))
		ret = built_env(data->env);
	else if (!ft_strncmp(get_cmd_name(data->cmds[cmd]), "cd", 2))
		ret = built_cd(data->cmds[cmd], data);
	else if (!ft_strncmp(get_cmd_name(data->cmds[cmd]), "export", 6))
		ret = built_export(data->cmds[cmd], data);
	else if (!ft_strncmp(get_cmd_name(data->cmds[cmd]), "exit", 4))
		ret = built_exit(data->cmds[cmd], data);
	else if (!ft_strncmp(data->cmds[cmd].line, "unset", 5))
		ret = built_unset(data->cmds[cmd], data);
	return (ret);
}

char	*get_cmd_name(t_cmd cmd)
{
	t_tkn	*cpy;

	cpy = cmd.tkn;
	while (cpy)
	{
		if (cpy->type < TYPE_REDIN)
			return (cpy->content);
		cpy = cpy->next;
	}
	return (NULL);
}
