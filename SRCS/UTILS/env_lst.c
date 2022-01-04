#include "../../minishell.h"
#include <stdlib.h>

t_envar *new_env(char **env)
{
	t_envar *lst;

	lst = malloc(sizeof(t_envar));
	if (lst == NULL)
		return (NULL);
	lst->str = ft_strdup(env[0]);
	lst->next = NULL;
	return (lst);
}

t_envar	*add_env(t_envar **lst, char *str)
{
	t_envar	tmp;
	t_envar *save;

	save = *lst;
	tmp.str = ft_strdup(str);
	if (tmp.str == NULL)
		return (NULL);
	tmp.next = NULL;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = &tmp;
	*lst = save;
	return (*lst);
}

t_envar	*init_env(char **env)
{
	t_envar	*envlst;
	int i;

	i = -1;
	envlst = new_env(env);
	if (envlst == NULL)
		return (NULL);
	while (env[++i])
		add_env(&envlst, env[i]);
	return (envlst);
}
