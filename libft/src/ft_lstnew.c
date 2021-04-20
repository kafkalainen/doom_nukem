/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:07:38 by jnivala           #+#    #+#             */
/*   Updated: 2020/06/25 12:24:55 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new;

	new = (t_list*)malloc(sizeof(*new));
	if (new != NULL)
	{
		if (content != NULL)
		{
			new->content = (void*)malloc(sizeof(*content) * content_size);
			if (new->content != NULL)
			{
				new->content = ft_memcpy(new->content, content, content_size);
				new->content_size = content_size;
			}
		}
		else
		{
			new->content = NULL;
			new->content_size = 0;
		}
		new->next = NULL;
		return (new);
	}
	free(new);
	new = NULL;
	return (new);
}
