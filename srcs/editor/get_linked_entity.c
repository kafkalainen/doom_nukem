/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_linked_entity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 08:44:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 08:46:30 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_entity_list	*get_linked_entity(t_entity_list **list, int link)
{
	t_entity_list	*tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->is_linked == link)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
