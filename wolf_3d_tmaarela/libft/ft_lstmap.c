/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:27:08 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/08 20:39:30 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *head, t_list *(*func)(t_list *link))
{
	t_list	*start;
	t_list	*link;

	start = NULL;
	while (head != NULL && (link = func(head)) != NULL)
	{
		if (start == NULL)
			start = link;
		else
			ft_lstadd_back(start, link);
		head = head->next;
	}
	if (link == NULL && start != NULL)
	{
		ft_lstdel(&start, &ft_lstfree);
	}
	return (start);
}
