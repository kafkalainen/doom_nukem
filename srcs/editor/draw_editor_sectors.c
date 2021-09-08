/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor_sectors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:02:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/08 17:16:40 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_wall_bbox(t_editor_walls *wall, t_sector_list *cur_sector,
		t_editor *editor)
{
	t_box	box;
	Uint32	color;

	box.start = world_to_screen(wall->bbox.start, editor->action.scalarf,
				editor->action.offsetf, &editor->buffer);
	box.end = world_to_screen(wall->bbox.end, editor->action.scalarf,
				editor->action.offsetf, &editor->buffer);
	if (wall->idx == editor->action.selected_wall
		&& cur_sector->idx_sector == editor->action.selected_sector)
		color = get_color(white);
	else
		color = get_color(yellow);
	if (cur_sector->idx_sector == editor->action.selected_sector)
		draw_box(box, &editor->buffer, color);
}

static void	draw_line_to_mouse_cursor(int active, t_editor_walls *wall,
			t_editor *editor)
{
	if (editor->action.edit_sector && active > 0)
	{
		draw_line(
			world_to_screen(
				vec2(wall->x0.x, wall->x0.y),
				editor->action.scalarf, editor->action.offsetf,
				&editor->buffer),
			vec2(editor->mouse_data.x, editor->mouse_data.y),
			white, &editor->buffer);
	}
}

static void	draw_wall_line(t_editor_walls *left_point, t_editor_walls *right_point,
			t_editor *editor)
{
	draw_line(
		world_to_screen(vec2(left_point->x0.x, left_point->x0.y),
			editor->action.scalarf, editor->action.offsetf, &editor->buffer),
		world_to_screen(vec2(right_point->x0.x, right_point->x0.y),
			editor->action.scalarf, editor->action.offsetf, &editor->buffer),
		get_color(white), &editor->buffer);
}

void	draw_editor_sectors(t_editor *editor)
{
	int				i;
	t_sector_list	*sector_list;
	t_editor_walls	*left_point;
	t_editor_walls	*right_point;

	sector_list = editor->sector_list;
	while (sector_list)
	{
		i = 0;
		left_point = sector_list->walls;
		right_point = left_point;
		// draw_bbox_sector(sector_list, &editor->buffer, &editor->action);
		while (left_point && left_point->next && i < sector_list->nb_of_walls)
		{
			draw_wall_bbox(left_point, sector_list, editor);
			right_point = left_point->next;
			draw_wall_line(left_point, right_point, editor);
			i++;
			left_point = left_point->next;
		}
		if (sector_list->idx_sector == editor->action.selected_sector
			&& editor->action.edit_sector)
			i = sector_list->nb_of_walls;
		sector_list = sector_list->next;
	}
	draw_line_to_mouse_cursor(i, left_point, editor);
}
