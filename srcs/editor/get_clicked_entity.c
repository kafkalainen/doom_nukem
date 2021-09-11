/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clicked_entity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:33:29 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/11 12:39:43 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_entity_list	*get_clicked_entity(t_entity_list **list, t_xy click,
				int *selected_entity)
{
	t_entity_list	*temp;
	t_entity_list	*selected;
	float			distance[2];

	selected = NULL;
	temp = *list;
	distance[1] = 9000.0f;
	while (temp != NULL)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end, click))
		{
			distance[0] = vec2_eucl_dist(click, vec2(temp->pos.x,
				temp->pos.z));
			if (distance[0] < distance[1])
			{
				selected = temp;
				*selected_entity = temp->entity_idx;
				distance[1] = distance[0];
			}
		}
		temp = temp->next;
	}
	if (selected)
		return (selected);
	*selected_entity = -1;
	return (NULL);
}
