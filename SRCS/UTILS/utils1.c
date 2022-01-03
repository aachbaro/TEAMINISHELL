/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:25:54 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/22 15:58:10 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	aff_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	del_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	del_cmd(t_data *data)
{
	int		i;

	i = 0;
	while (data->cmds[i].line)
	{
		free(data->cmds[i].line);
		free(data->cmds[i].path);
		del_tab(data->cmds[i].args);
		tkn_clear(&data->cmds[i].tkn);
		i++;
	}
	free(data->cmds);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*cpy;

	cpy = malloc(sizeof(char) * (n + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

void	free_all(t_data *data)
{
	if (data->old_line)
		free(data->old_line);
	if (data->cmds->line)
		del_cmd(data);
}
