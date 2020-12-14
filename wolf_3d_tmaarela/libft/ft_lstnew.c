/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:49:33 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/12 13:31:04 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*link;

	if ((link = (t_list *)malloc(sizeof(t_list))))
	{
		link->next = NULL;
		link->content = NULL;
		link->content_size = 0;
		if (content && (link->content = malloc(content_size)))
		{
			ft_memcpy(link->content, content, content_size);
			link->content_size = content_size;
		}
	}
	return (link);
}
