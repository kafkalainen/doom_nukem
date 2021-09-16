/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor_sectors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:02:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/16 10:20:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_wall_bbox(t_editor_walls *wall, t_editor_sector *cur_sector,
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
	if (editor->action.create_sector == user_input && active > 0)
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

static void	draw_wall_line(t_editor_walls *left_point,
	t_editor_walls *right_point, t_editor *editor, Uint32 color)
{
	t_xy	left;
	t_xy	right;

	left = world_to_screen(vec2(left_point->x0.x, left_point->x0.y),
			editor->action.scalarf, editor->action.offsetf, &editor->buffer);
	right = world_to_screen(vec2(right_point->x0.x, right_point->x0.y),
			editor->action.scalarf, editor->action.offsetf, &editor->buffer);
	draw_line(left, right, color, &editor->buffer);
	if (left.y != right.y)
		draw_line(vec2(left.x + 1, left.y), vec2(right.x + 1, right.y),
			color, &editor->buffer);
	else
		draw_line(vec2(left.x, left.y + 1), vec2(right.x, right.y + 1),
			color, &editor->buffer);
}

void	draw_editor_sector(t_editor *editor, t_editor_sector *sector_list,
	t_editor_walls *left_point, Uint32 color)
{
	int				i;

	while (sector_list)
	{
		i = 0;
		left_point = sector_list->walls;
		while (left_point && left_point->next && i < sector_list->nb_of_walls)
		{
			if (sector_list->idx_sector == editor->action.selected_sector
				&& i == editor->action.selected_wall)
				color = get_color(red);
			else
				color = get_color(white);
			draw_wall_bbox(left_point, sector_list, editor);
			draw_wall_line(left_point, left_point->next, editor, color);
			i++;
			left_point = left_point->next;
		}
		if (sector_list->idx_sector == editor->action.selected_sector
			&& editor->action.create_sector == user_input)
			i = sector_list->nb_of_walls;
		sector_list = sector_list->next;
	}
	draw_line_to_mouse_cursor(i, left_point, editor);
}

void	draw_editor_sectors(t_editor *editor)
{
	t_editor_sector	*sector_list;
	t_editor_walls	*left_point;
	Uint32			color;

	color = 0;
	left_point = NULL;
	sector_list = editor->sector_list;
	draw_editor_sector(editor, sector_list, left_point, color);
	draw_sector_special_info(editor);
}
