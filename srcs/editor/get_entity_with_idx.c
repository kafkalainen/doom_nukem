/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_entity_with_idx.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 09:24:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 09:25:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_entity_list	*get_entity_with_idx(t_entity_list **list, int idx)
{
	t_entity_list	*tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->entity_idx == idx)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
