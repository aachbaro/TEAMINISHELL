/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_to_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:54:05 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/17 17:06:17 by aachbaro         ###   ########.fr       */
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

char	*get_path(char *cmd)
{
	char	*path;
	char	**tab;
	int		i;

	path = ft_strdup(getenv("PATH"));
	if (!path)
		return (NULL);
	tab = ft_split(path, ':');
	free(path);
	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		// Ici on chope un path a tester pour voir si lexecutable est la
		path = get_possible_path(cmd, tab[i]);
		if (!path)
			return (NULL);
		// Ensuite on test avec access si lexxecutable est bon
		// si cest le cas on renvoie ce path
		if (!access(path, F_OK))
		{
			del_tab(tab);
			return (path);
		}
		// Sinon on test un autre path
		free(path);
		i++;
	}
	del_tab(tab);
	// Si on a pas trouver le path on renvoie la commande de base
	// Ca peut etre dans le cas ou cest un builtins ducoup on a juste besoin
	// du nom de la commande
	return (ft_strdup(cmd));
}

char	**get_args(t_cmd cmd)
{
	t_tkn	*cpy;
	int		i;
	char	**tab;

	cpy = cmd.tkn;
	i = 0;
	// La on chope tous les arguments a la suite avant de tomber sur une
	// redirection
	while (cpy && cpy->type < TYPE_REDIN)
	{
		i++;
		cpy = cpy->next;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	cpy = cmd.tkn;
	i = 0;
	while (cpy && cpy->type < TYPE_REDIN)
	{
		tab[i] = ft_strdup(cpy->content);
		if (!tab[i])
			return (NULL);
		i++;
		cpy = cpy->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	tkn_to_exe(t_data *data, int cmd)
{
	// En premier je cherche le bon path avec la fonction get path plus haut
	// Peut etre a revoir et checker avant si cest un builtin pour pas chercher
	// le path si on est pas cense lutiliser.
	data->cmds[cmd].path = get_path(data->cmds[cmd].tkn->content);
	if (!data->cmds[cmd].path)
		return (-1);
	// Ensuite remplir le tableau dargument (bien checker les structures
	// pour comprendre ce quon rempli dans le parsing)
	data->cmds[cmd].args = get_args(data->cmds[cmd]);
	if (!data->cmds[cmd].args)
		return (-1);
	return (0);
}
