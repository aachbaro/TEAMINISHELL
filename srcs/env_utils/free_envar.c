#include "../../minishell.h"

/*
 * free environnement variable
 * free memory of an envar node (str, key, value)
 */

void	free_envar(t_envar *var)
{
	if (var && var->str && var->key && var->value)
	{
		free(var->str);
		free(var->key);
		free(var->value);
		free(var);
	}
}
