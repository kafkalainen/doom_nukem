/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clicked_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:21:26 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/11 12:29:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_editor_walls	*get_clicked_wall(t_editor_walls **walls, t_xy click,
				int *selected_wall, int nbr_of_walls)
{
	float			distance[2];
	t_editor_walls	*temp;
	t_editor_walls	*selected;

	selected = NULL;
	temp = *walls;
	distance[1] = 9000.0f;
	while (temp != NULL && nbr_of_walls--)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end, click))
		{
			distance[0] = vec2_eucl_dist(click, vec2(temp->x0.x, temp->x0.y));
			if (distance[0] < distance[1])
			{
				selected = temp;
				*selected_wall = temp->idx;
				distance[1] = distance[0];
			}
		}
		temp = temp->next;
	}
	if (selected)
		return (selected);
	*selected_wall = -1;
	return (NULL);
}
