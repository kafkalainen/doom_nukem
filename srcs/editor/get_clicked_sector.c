/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clicked_sector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:19:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/11 12:28:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_editor_sector	*get_clicked_sector(t_editor_sector **list, t_xy click,
				int *selected_sector)
{
	t_editor_sector	*temp;
	t_editor_sector	*selected;
	float			distance[2];

	selected = NULL;
	temp = *list;
	distance[1] = 9000.0f;
	while (temp != NULL)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end, click))
		{
			distance[0] = vec2_eucl_dist(click, temp->centroid);
			if (distance[0] < distance[1])
			{
				selected = temp;
				*selected_sector = temp->idx_sector;
				distance[1] = distance[0];
			}
		}
		temp = temp->next;
	}
	if (selected)
		return (selected);
	*selected_sector = -1;
	return (NULL);
}
