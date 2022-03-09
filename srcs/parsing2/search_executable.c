/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:54:05 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/09 16:42:40 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_possible_path(char *cmd, char *str)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(str, "/");
	if (!tmp)
		return (NULL);
	ret = ft_strjoin(tmp, cmd);
	free(tmp);
	return (ret);
}

char	*path_loop(char *path_line, char *cmd)
{
	int		i;
	char	*path;
	char	**tab;

	i = 0;
	tab = ft_split(path_line, ':');
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		path = get_possible_path(cmd, tab[i]);
		if (!path || !access(path, F_OK))
		{
			del_tab(tab);
			return (path);
		}
		free(path);
		i++;
	}
	del_tab(tab);
	return (ft_strdup(""));
}

char	*get_path(char *cmd, t_envar *env)
{
	t_dblquote_parser	p;

	p.tmp = NULL;
	if (!cmd)
		return (ft_strdup(""));
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	if (find_envar(env, "PATH"))
		p.tmp = ft_strdup(find_envar(env, "PATH")->value);
	if (!p.tmp)
	{
		g_g.exit = 127;
		printf("%s: No such file or directory\n", cmd);
		return (ft_strdup(""));
	}
	p.tmp2 = path_loop(p.tmp, cmd);
	free(p.tmp);
	if (!p.tmp2[0])
	{
		printf("%s: Command not found\n", cmd);
		g_g.exit = 127;
	}
	return (p.tmp2);
}

int	get_nb_args(t_tkn *tkn)
{
	t_tkn	*cpy;
	int		i;

	cpy = tkn;
	i = 0;
	while (cpy)
	{
		if (cpy->type <= TYPE_VAR)
			i++;
		cpy = cpy->next;
	}
	return (i);
}

char	**get_args(t_cmd cmd)
{
	t_tkn	*cpy;
	int		i;
	char	**tab;

	cpy = cmd.tkn;
	tab = malloc(sizeof(char *) * (get_nb_args(cmd.tkn) + 1));
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
