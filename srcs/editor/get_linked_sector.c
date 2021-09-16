/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_linked_sector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:32:13 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/16 10:59:05 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_editor_sector	*get_linked_sector(t_editor_sector **list, int link,
				int cur_idx)
{
	t_editor_sector	*tmp;

	tmp = *list;
	if (link == 0 || link == 1)
		return (NULL);
	while (tmp != NULL)
	{
		if (tmp->idx_sector == link - 2 && tmp->idx_sector != cur_idx)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_uint	calc_linked_sectors(t_editor_sector **list, int link,
		int link_type)
{
	t_editor_sector	*tmp;
	t_uint			links;

	tmp = *list;
	links = 0;
	if (link == 0 || link == 1)
		return (links);
	while (tmp != NULL)
	{
		if (tmp->idx_sector == link - 2 && is_linkable_entity(link_type))
			links++;
		tmp = tmp->next;
	}
	return (links);
}
