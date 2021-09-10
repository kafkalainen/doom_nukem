/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_another_sector_is_inside.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:45:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/10 16:10:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_if_another_sector_is_inside(t_editor_sector *tested,
		t_editor_sector **head)
{
	int				i;
	t_editor_walls	*cur_wall;
	t_editor_sector	*temp;
	t_editor_sector	*original_head;

	temp = *head;
	original_head = *head;
	while (temp->next)
	{
		i = 0;
		cur_wall = temp->walls;
		while (i < tested->nb_of_walls)
		{
			if (check_bbox(tested->bbox.start, tested->bbox.end,
					vec2(cur_wall->x0.x, cur_wall->x0.y)))
				return (true);
			cur_wall = cur_wall->next;
			i++;
		}
		temp = temp->next;
	}
	temp = original_head;
	return (false);
}
