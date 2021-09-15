/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor_sector_bbox.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 09:31:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 19:24:14 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_bbox_sector(t_editor_sector *sector, t_buffer *buffer,
		t_action *action)
{
	Uint32	color;
	t_box	bbox_scaled;

	bbox_scaled.start = world_to_screen(sector->bbox.start, action->scalarf,
			action->offsetf, buffer);
	bbox_scaled.end = world_to_screen(sector->bbox.end, action->scalarf,
			action->offsetf, buffer);
	if (action->selected_sector == sector->idx_sector)
		color = get_color(wheat);
	else
		color = get_color(gray);
	draw_box(bbox_scaled, buffer, color);
}

void	draw_editor_sectors_bboxes(t_editor *editor, t_action *action)
{
	t_editor_sector	*sector_list;

	sector_list = editor->sector_list;
	while (sector_list)
	{
		if (action->selected_sector != sector_list->idx_sector)
			draw_bbox_sector(sector_list, &editor->buffer, &editor->action);
		sector_list = sector_list->next;
	}
	sector_list = editor->sector_list;
	while (sector_list)
	{
		if (action->selected_sector == sector_list->idx_sector)
			draw_bbox_sector(sector_list, &editor->buffer, &editor->action);
		sector_list = sector_list->next;
	}
}
