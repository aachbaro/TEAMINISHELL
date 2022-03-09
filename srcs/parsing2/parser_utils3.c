/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:25:12 by aachbaro          #+#    #+#             */
/*   Updated: 2022/03/09 17:01:52 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_state_quote(char c, int *dbl, int *smpl)
{
	if (c == '\'' && *dbl == 0 && *smpl == 0)
		*smpl = 1;
	else if (c == '\'' && *dbl == 0 && *smpl == 1)
		*smpl = 0;
	else if (c == '"' && *smpl == 0 && *dbl == 0)
		*dbl = 1;
	else if (c == '"' && *smpl == 0 && *dbl == 1)
		*dbl = 0;
}

int	cmd_count(char *str)
{
	int	i;
	int	cmd;
	int	smpl;
	int	dbl;

	i = 0;
	smpl = 0;
	dbl = 0;
	cmd = 1;
	while (str[i])
	{
		set_state_quote(str[i], &dbl, &smpl);
		if (str[i] == '|' && smpl == 0 && dbl == 0)
			cmd++;
		i++;
	}
	return (cmd);
}

int	is_pipe_sep(char c, t_dblquote_parser *p)
{
	if (c == '|' && !(p->dbl + p->smpl))
		return (1);
	return (0);
}

char	**split_pipe(char *str)
{
	t_dblquote_parser	p;
	char				**tab;

	p.i = 0;
	p.k = 0;
	p.smpl = 0;
	p.dbl = 0;
	tab = malloc(sizeof(char *) * (cmd_count(str) + 1));
	if (!tab)
		return (NULL);
	while (str[p.i])
	{
		p.j = p.i;
		while (str[p.j] && !is_pipe_sep(str[p.j], &p))
			set_state_quote(str[p.j++], &p.dbl, &p.smpl);
		tab[p.k] = ft_strndup(str + p.i, p.j - p.i);
		if (!tab[p.k])
			return (NULL);
		if (str[p.j] == '|')
			p.j++;
		p.i = p.j;
		p.k++;
	}
	tab[p.k] = 0;
	return (tab);
}
