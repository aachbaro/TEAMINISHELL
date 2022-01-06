/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:46:10 by aachbaro          #+#    #+#             */
/*   Updated: 2021/12/17 18:11:36 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	line_to_exe(t_data *data)
{
	int	i;

	i = 0;
	// On fait un split de la ligne sur les pipe
	// Puis creer une liste chainee de token pour chaque "mot" de la commande
	// a la fin on a un tableau de commande qui contien pour chaque element:
	// la commande en entier en char*, le path de la commande, 
	// les arguments et la liste chainee de tkn, chaque tkn a un char* du "mot"
	// et le type du mot entre par rxemple "<<" ou une variable "$"
	// ces structures sont remplie dans les fonction line to token puis
	// tkn to exe, dans tkn  
	if (line_to_tokens(data) == -1)
		return (-1);
	while (data->cmds[i].line)
	{
		if (tkn_to_exe(data, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	prompt(t_data *data)
{
	// On recupere la commande entree par l'utilsateur
	data->line = readline("~>");
	// Check si on doit rentrer la ligen dans lhistorique
	printf("DEBUG::%s::\n", data->line);
	if (!data->line)
		return (-1);
	if (!data->old_line || (ft_strncmp(data->line, data->old_line,
		ft_strlen(data->line)) || ft_strlen(data->old_line)
			!= ft_strlen(data->line)))
		add_history(data->line);
	free(data->old_line);
	data->old_line = ft_strdup(data->line);
	if (!data->old_line)
		return (-1);
	return (0);
}
