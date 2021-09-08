/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor_sectors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:02:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/08 15:01:39 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_editor_sectors(t_editor *editor)
{
	t_sector_list	*sector_list;
	t_editor_walls	*wall_1;
	t_editor_walls	*wall_2;
	// t_xy			test1;
	// t_xy			test2;
	// t_box			temp_box;
	int				active;
	// Uint32			color;

	active = 0;
	sector_list = editor->sector_list;
	while (sector_list)
	{
		wall_1 = sector_list->walls;
		wall_2 = wall_1;
		// draw_bbox_sector(sector_list, &editor->buffer, &editor->action);
		while (wall_1 && wall_1->next && active < sector_list->nb_of_walls)
		{
			// test1 = world_to_screen((t_screen_xy){wall_1->bbox.start.x, wall_1->bbox.start.y}, editor->action.scalarf, editor->action.offsetf,
			// 			&editor->buffer);
			// test2 = world_to_screen((t_screen_xy){wall_1->bbox.end.x, wall_1->bbox.end.y}, editor->action.scalarf, editor->action.offsetf,
			// 			&editor->buffer);
			// temp_box.start = test1;
			// temp_box.end = test2;
			// if (wall_1->idx == editor->action.selected_wall && sector_list->idx_sector == editor->action.selected_sector)
			// 	color = get_color(white);
			// else
			// 	color = get_color(yellow);
			// if (sector_list->idx_sector == editor->action.selected_sector)
			// 	draw_box(temp_box, &editor->buffer, color);
			wall_2 = wall_1->next;
			draw_line(
				world_to_screen(wall_1->x0, editor->action.scalarf, editor->action.offsetf,
					&editor->buffer),
				world_to_screen(wall_2->x0, editor->action.scalarf, editor->action.offsetf,
					&editor->buffer),
				get_color(white), &editor->buffer);
			active++;
			wall_1 = wall_1->next;
		}
		active = 0;
		if (sector_list->idx_sector == editor->action.selected_sector)
			active = sector_list->nb_of_walls;
		sector_list = sector_list->next;
	}
	if (editor->action.edit_sector && active > 0)
		draw_line(
			world_to_screen(wall_2->x0, editor->action.scalarf, editor->action.offsetf,
				&editor->buffer),
			vec2(editor->mouse_data.x, editor->mouse_data.y),
			white, &editor->buffer);
}
