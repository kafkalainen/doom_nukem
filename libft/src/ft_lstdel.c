/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 08:47:38 by jnivala           #+#    #+#             */
/*   Updated: 2020/06/25 14:20:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *item;

	while (*alst != NULL)
	{
		item = *alst;
		*alst = item->next;
		del(item->content, item->content_size);
		free(item);
		item = NULL;
	}
}
