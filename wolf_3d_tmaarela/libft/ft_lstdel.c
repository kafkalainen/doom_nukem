/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:03:33 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/08 21:54:56 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **head, void (*del)(void *, size_t))
{
	if (*head != NULL)
	{
		if ((*head)->next != NULL)
			ft_lstdel(&(*head)->next, del);
		del((*head)->content,
			(*head)->content_size);
		free(*head);
		*head = NULL;
	}
}
