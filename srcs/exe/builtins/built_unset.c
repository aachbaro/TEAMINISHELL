#include "../../../minishell.h"

/*
 * unset 
 * Let you unset any variable
 */ 

void	remove_var(t_envar **env, char *name)
{
	t_envar *curr;
	t_envar *prev;

	curr = *env;
	prev = *env;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, name) == 0)
		{
			prev->next = curr->next;
			free_envar(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	built_unset(t_cmd cmd, t_envar **env)
{
	t_tkn *cpy;

	cpy = cmd.tkn->next;
	if (!cpy)
		return (EXIT_SUCCESS);
	while (cpy->type < 4)
	{
		remove_var(env, cpy->content);
		cpy = cpy->next;
	}
	return (EXIT_SUCCESS);
}
