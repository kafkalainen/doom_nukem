/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_linked_entity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 08:44:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 10:26:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_entity_list	*get_linked_entity(t_entity_list **list, int link, int cur_idx)
{
	t_entity_list	*tmp;

	tmp = *list;
	if (link == 0 || link == 1)
		return (NULL);
	while (tmp != NULL)
	{
		if (tmp->is_linked == link && tmp->entity_idx != cur_idx)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
