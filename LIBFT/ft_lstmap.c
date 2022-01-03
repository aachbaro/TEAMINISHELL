/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:46:17 by aachbaro          #+#    #+#             */
/*   Updated: 2021/09/01 15:41:40 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newlink;
	t_list	*ptr;

	if (!lst)
		return (NULL);
	newlist = NULL;
	ptr = lst;
	while (ptr)
	{
		newlink = ft_lstnew((*f)(ptr->content));
		if (!newlink)
		{
			ft_lstclear(&newlist, (*del));
			return (NULL);
		}
		ft_lstadd_back(&newlist, newlink);
		ptr = ptr->next;
	}
	return (newlist);
}
