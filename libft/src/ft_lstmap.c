/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 08:51:18 by jnivala           #+#    #+#             */
/*   Updated: 2020/07/09 11:55:16 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_lst_push_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (*alst == NULL)
		*alst = new;
	else
	{
		temp = *alst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
}

static t_list	*ft_lstdelbasicelement(t_list **alst)
{
	t_list *item;

	while (*alst != NULL)
	{
		item = *alst;
		*alst = item->next;
		if (item->content != NULL)
			(ft_memdel(&(item->content)));
		free(item);
		item = NULL;
	}
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*temp;
	t_list	*modified_elem;

	new = NULL;
	if (lst == NULL)
		return (NULL);
	temp = lst;
	while (temp != NULL)
	{
		modified_elem = f(temp);
		if (modified_elem == NULL)
			return (ft_lstdelbasicelement(&new));
		ft_lst_push_back(&new, f(temp));
		temp = temp->next;
	}
	return (new);
}
