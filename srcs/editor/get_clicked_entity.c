/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clicked_entity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:33:29 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/13 11:34:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_entity_list	*get_clicked_entity(t_entity_list **list, t_xy click,
				int *selected_entity)
{
	t_entity_list	*tmp;
	t_entity_list	*selected;
	float			distance[2];

	selected = NULL;
	tmp = *list;
	distance[1] = 9000.0f;
	while (tmp != NULL)
	{
		if (check_bbox(tmp->bbox.start, tmp->bbox.end, click))
		{
			distance[0] = vec2_eucl_dist(click, vec2(tmp->pos.x, tmp->pos.z));
			if (distance[0] < distance[1])
			{
				selected = tmp;
				*selected_entity = tmp->entity_idx;
				distance[1] = distance[0];
			}
		}
		tmp = tmp->next;
	}
	if (selected)
		return (selected);
	*selected_entity = -1;
	return (NULL);
}
