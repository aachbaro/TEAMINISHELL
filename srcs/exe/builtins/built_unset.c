#include "../../../minishell.h"

/*
 * unset 
 * Let you unset any variable
 */ 

int	built_unset(t_cmd cmd, t_data *data)
{
	t_tkn *cpy;

	cpy = cmd.tkn->next;
	if (!cpy)
		return (EXIT_FAILURE);
	while (cpy && cpy->type < 4)
	{
		remove_var(&(data->env), cpy->content);
		cpy = cpy->next;
	}
	return (EXIT_SUCCESS);
}
