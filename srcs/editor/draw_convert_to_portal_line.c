/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_convert_to_portal_line.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:03:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/14 14:10:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_convert_to_portal_line(t_editor *editor)
{
	t_editor_sector	*temp;
	t_editor_sector	*head;

	temp = editor->sector_list;
	head = editor->sector_list;
	while (temp != NULL && temp->idx_sector != editor->action.prev_sector)
		temp = temp->next;
	if (temp)
	{
		draw_line(
			world_to_screen(vec2(temp->centroid.x, temp->centroid.y),
				editor->action.scalarf, editor->action.offsetf,
				&editor->buffer),
			world_to_screen(vec2(editor->action.world_pos.x,
				editor->action.world_pos.y), editor->action.scalarf,
				editor->action.offsetf, &editor->buffer),
				get_color(blue), &editor->buffer);
	}
	editor->sector_list = head;
}
