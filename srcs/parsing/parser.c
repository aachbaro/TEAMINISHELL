/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:46:10 by aachbaro          #+#    #+#             */
/*   Updated: 2022/01/14 16:37:53 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * On fait un split de la ligne sur les pipe
 * Puis creer une liste chainee de token pour chaque "mot" de la commande
 * a la fin on a un tableau de commande qui contien pour chaque element:
 * la commande en entier en char*, le path de la commande, 
 * les arguments et la liste chainee de tkn, chaque tkn a un char* du "mot"
 * et le type du mot entre par rxemple "<<" ou une variable "$"
 * ces structures sont remplie dans les fonction line to token puis
 * tkn to exe, dans tkn\
 */

int	line_to_exe(t_data *data)
{
	int	i;

	i = 0;
	if (input_to_tokens(data) == -1)
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
	data->usr_input = readline("~>");
	// Check si on doit rentrer la ligen dans lhistorique
<<<<<<< HEAD
	data->env = data->env->next;
	printf("DEBUG::%s\n%s\n%s::\n", data->line, data->env->key, data->env->value);
	if (!data->line)
=======
	printf("DEBUG::%s::\n", data->usr_input);
	if (!data->usr_input)
>>>>>>> 7fbb44dd4719b80f22e85d74e84e6634f3af684c
		return (-1);
	if (!data->prev_input || (ft_strncmp(data->usr_input, data->prev_input,
		ft_strlen(data->usr_input)) || ft_strlen(data->prev_input)
			!= ft_strlen(data->usr_input)))
		add_history(data->usr_input);
	free(data->prev_input);
	data->prev_input = ft_strdup(data->usr_input);
	if (!data->prev_input)
		return (-1);
	return (0);
}
