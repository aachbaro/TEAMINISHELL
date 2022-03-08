/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:54:05 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/08 12:31:18 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char 	*get_possible_path(char *cmd, char *str)
{
	char *ret;
	char *tmp;

	tmp = ft_strjoin(str, "/");
	if (!tmp)
		return (NULL);
	ret = ft_strjoin(tmp, cmd);
	free(tmp);
	return (ret);
}

char	*get_path(char *cmd, t_envar *env)
{
	char	*path;
	char	**tab;
	int		i;

	if (!cmd)
		return (ft_strdup(""));
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	if (find_envar(env, "PATH"))
		path = ft_strdup(find_envar(env, "PATH")->value);
	else
		path = NULL;
	if (!path)
	{
		g_g.exit = 127;
		printf("%s: No such file or directory\n", cmd);
		return (ft_strdup(""));
	}
	tab = ft_split(path, ':');
	free(path);
	if (!tab)
		return (NULL);
	i = 0;
	if (cmd[0])
	{
		while (tab[i])
		{
			path = get_possible_path(cmd, tab[i]);
			if (!path)
				return (NULL);
			if (!access(path, F_OK))
			{
				del_tab(tab);
				return (path);
			}
			free(path);
			i++;
		}
	}
	del_tab(tab);
	printf("%s: Command not found\n", cmd);
	g_g.exit = 127;
	return (ft_strdup(""));
}

char	**get_args(t_cmd cmd)
{
	t_tkn	*cpy;
	int	i;
	char	**tab;

	cpy = cmd.tkn;
	i = 0;
	while (cpy)
	{
		if (cpy->type <= TYPE_VAR)
			i++;
		cpy = cpy->next;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	cpy = cmd.tkn;
	i = 0;
	while (cpy)
	{
		if (cpy->type <= TYPE_VAR)
		{
			tab[i] = ft_strdup(cpy->content);
			if (!tab[i])
				return (NULL);
			i++;
		}
		cpy = cpy->next;
	}
	tab[i] = NULL;
	return (tab);
}
