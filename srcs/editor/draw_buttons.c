/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:35 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/06 14:16:10 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

void	draw_bbox_sector(t_sector_list *sector, t_buffer *buffer, t_action *action)
{
	float	point1;
	float	point2;
	float	point3;
	float	point4;
	int		color;

	point1 = sector->bbox.start.x * action->scalar + action->offset.x;
	point2 = sector->bbox.start.y * action->scalar + action->offset.y;
	point3 = sector->bbox.end.x * action->scalar + action->offset.x;
	point4 = sector->bbox.end.y * action->scalar + action->offset.y;
	if (action->selected_sector == sector->idx_sector)
		color = lightgreen;
	else
		color = blue;
	draw_rect(vec2(point1, point2), vec2(fabs(point1 - point3), fabs(point2 - point4)), buffer, color);
}

void	draw_box(t_box box, t_buffer *buffer, int color)
{
	float end;
	float start;

	end = box.end.y;
	start = box.start.y;
	box.end.y = box.start.y;
	while (start < end)
	{
		box.start.y = start;
		box.end.y = box.start.y;
		draw_line(box.start, box.end, color, buffer);
		start++;
	}
}

void		draw_sector_textfields(t_sector_list *sector, t_buffer *buffer)
{
	t_plx_modifier	mod;

	if (!sector)
		return ;
	mod.colour = white;
	mod.size = TEXT_SIZE;
	c_pxl(buffer, vec2(165, 56), '0' + sector->idx_sector, mod);
	if (sector->sector_plot)
		str_pxl(buffer, vec2(32, 580), (char *)sector->sector_plot, mod);
}

int			get_color_from_action_data(int i, t_action *action, int end_sector)
{
	if ((i == 7 && action->player_start_assigned) || (i == 4 && end_sector >= 0))
		return (green);
	else if (i == 7 || i == 4)
		return (red);
	return (white);
}

void		draw_buttons(t_button **blist, t_buffer *buffer, int draw_depth, t_action *action, int end_sector)
{
	int				i;
	t_box			box;
	t_plx_modifier	mod;

	box.start = vec2(0, 0);
	box.end = vec2(300, buffer->height);
	draw_box(box, buffer, 0x282040);
	i = 0;
	mod.colour = white;
	mod.size = TEXT_SIZE;
	while (i < NBR_BUTTONS)
	{
		if (blist[i]->info.draw_depth == draw_depth)
		{
			mod.colour = get_color_from_action_data(i, action, end_sector);
			box.start = blist[i]->ltop;
			box.end = blist[i]->wh;
			draw_box(box, buffer, 0xAAAAAA);
			str_pxl(buffer,
				vec2(blist[i]->ltop.x + 8, blist[i]->ltop.y + 4),
				blist[i]->info.text, mod);
		}
		i++;
	}
}

void			draw_grid_editor(t_buffer *buffer, t_action *action)
{
	int		cells_on_sx;
	int		cells_on_sy;
	int		i;
	int		val;

	cells_on_sx = (buffer->width - 300) / action->scalar;
	cells_on_sy = (buffer->height) / action->scalar;
	i = 0;
	while (i <= cells_on_sy)
	{
		val = i * action->scalar + (action->offset.y % action->scalar);
		if (val < buffer->height)
			draw_line(vec2(300, val),
				vec2(buffer->width, val), 0x808080, buffer);
		i++;
	}
	i = 0;
	while (i <= cells_on_sx)
	{
		val = (i * action->scalar + (action->offset.y % action->scalar)) + 300;
		if (val < buffer->width && val >= 300)
			draw_line(vec2(val, 0),
				vec2(val, buffer->height), 0x808080, buffer);
		i++;
	}
}

t_xy		scale_xy(t_screen_xy x0, int scalar, t_screen_xy offset)
{
	return ((t_xy){x0.x * scalar + offset.x, x0.y * scalar + offset.y, 1.0f});
}

void	draw_editor_sectors(t_editor *editor)
{
	t_sector_list	*sector_list;
	t_editor_walls	*wall_1;
	t_editor_walls	*wall_2;
	t_xy			test1;
	t_xy			test2;
	t_box			temp_box;
	int				active;
	int				color;

	active = 0;
	sector_list = editor->sector_list;
	while (sector_list)
	{
		wall_1 = sector_list->walls;
		wall_2 = wall_1;
		draw_bbox_sector(sector_list, &editor->buffer, &editor->action);
		while (wall_1 && wall_1->next && active < sector_list->nb_of_walls)
		{
			test1 = scale_xy((t_screen_xy){wall_1->bbox.start.x, wall_1->bbox.start.y}, editor->action.scalar, editor->action.offset);
			test2 = scale_xy((t_screen_xy){wall_1->bbox.end.x, wall_1->bbox.end.y}, editor->action.scalar, editor->action.offset);
			temp_box.start = test1;
			temp_box.end = test2;
			if (wall_1->idx == editor->action.selected_wall && sector_list->idx_sector == editor->action.selected_sector)
				color = white;
			else
				color = yellow;
			if (sector_list->idx_sector == editor->action.selected_sector)
				draw_box(temp_box, &editor->buffer, color);
			wall_2 = wall_1->next;
			draw_line(
				scale_xy(wall_1->x0, editor->action.scalar, editor->action.offset),
				scale_xy(wall_2->x0, editor->action.scalar, editor->action.offset),
				white, &editor->buffer);
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
			scale_xy(wall_2->x0, editor->action.scalar, editor->action.offset),
			vec2(editor->mouse_data.x, editor->mouse_data.y),
			white, &editor->buffer);
}

void	draw_entities(t_editor *editor)
{
	t_entity_list	*temp;
	t_entity_list	*head;
	t_entity_list	*link;
	t_xy			test1;
	t_xy			test2;
	t_box			temp_box;
	int				color;

	link = editor->entity_list;
	head = editor->entity_list;
	temp = editor->entity_list;
	while (temp != NULL)
	{
		test1 = scale_xy((t_screen_xy){temp->pos.x, temp->pos.z}, editor->action.scalar, editor->action.offset);
		test2 = scale_xy((t_screen_xy){temp->pos.x + 1, temp->pos.z + 1}, editor->action.scalar, editor->action.offset);
		temp_box.start = test1;
		temp_box.end = test2;
		if (temp->entity_idx == editor->action.selected_entity)
			color = white;
		else
			color = red;
		draw_box(temp_box, &editor->buffer, color);
		if (temp->is_linked)
		{
			while (link != NULL)
			{
				if (link->is_linked == temp->is_linked && link->is_linked > 1)
					draw_line(
						scale_xy((t_screen_xy){temp->pos.x, temp->pos.z}, editor->action.scalar, editor->action.offset),
						scale_xy((t_screen_xy){link->pos.x, link->pos.z}, editor->action.scalar, editor->action.offset),
						blue, &editor->buffer);
				link = link->next;
			}
			link = head;
		}
		temp = temp->next;
	}
	editor->entity_list = head;
}

void	draw_entity_textfields(t_entity_list **list, int selected_entity, t_buffer *buffer)
{
	t_entity_list	*temp;
	t_plx_modifier	mod;
	temp = *list;
	while (temp != NULL && temp->entity_idx != selected_entity)
		temp = temp->next;
	if (!temp)
		return ;
	mod.colour = white;
	mod.size = TEXT_SIZE;
	c_pxl(buffer, vec2(100, 56), '0' + temp->entity_idx, mod);
	c_pxl(buffer, vec2(100, 84), '0' + temp->entity_type, mod);
	c_pxl(buffer, vec2(150, 114), '0' + temp->is_linked, mod);
	c_pxl(buffer, vec2(165, 144), '0' + temp->is_revealed, mod);
	c_pxl(buffer, vec2(165, 174), '0' + temp->is_static, mod);
	c_pxl(buffer, vec2(100, 204), '0' + temp->state, mod);
}

void	draw_input_string(unsigned char *string, t_buffer *buffer, int midpoint, int help_text)
{
	t_plx_modifier	mod;

	mod.colour = white;
	mod.size = TEXT_SIZE;
	if (help_text == map_saving)
		str_pxl(buffer, vec2(midpoint - 100, 50), "Please input text string", mod);
	if (string != NULL)
		str_pxl(buffer, vec2(midpoint - 100, 70), (char *)string, mod);
}

void	update_editor_load_menu(t_buffer *buffer, t_action *action, char **map_names)
{
	int				y;
	int				i;
	t_plx_modifier	mod;
	t_box			box;

	if (action->keysym == SDLK_DOWN)
		get_menu_range_key_down(&action->option, &action->start, &action->end, action->nbr_of_maps);
	else if (action->keysym == SDLK_UP)
		get_menu_range_key_up(&action->option, &action->start, &action->end, action->nbr_of_maps);
	i = action->start;
	y = 0;
	mod.colour = orange;
	mod.size = TEXT_SIZE;
	if (action->link_maps)
		str_pxl(buffer, vec2(310, 70), "Select which map to link to", mod);
	else
		str_pxl(buffer, vec2(310, 70), "Select which map to load into editor", mod);
	box.start.x = 310;
	box.start.y = 100;
	box.end.x = 700;
	box.end.y = (100 + (15 * (action->end - action->start + 1)));
	draw_box(box, buffer, black);
	while (i <= action->end)
	{
		if (i == action->option)
			mod.colour = red;
		else
			mod.colour = white;
		str_pxl(buffer, vec2(310, 100 + y),
			map_names[i], mod);
		y += 15;
		i++;
	}
}

void	draw_ui(t_editor *editor)
{
	t_sector_list	*temp;
	t_entity_list	*ent;
	t_entity_list	*tempo;

	temp = editor->sector_list;
	if (editor->action.grid == 1)
		draw_grid_editor(&editor->buffer, &editor->action);
	while (temp && temp->idx_sector != editor->action.selected_sector)
		temp = temp->next;
	if (editor->action.draw_depth == entity)
		draw_entity_textfields(&editor->entity_list, editor->action.selected_entity, &editor->buffer);
	if (editor->action.draw_depth == sector)
		draw_sector_textfields(temp, &editor->buffer);
	draw_editor_sectors(editor);
	draw_entities(editor);
	ent = editor->entity_list;
	tempo = editor->entity_list;
	if (editor->action.link_entity == 1)
	{
		while (tempo->entity_idx != editor->action.selected_entity)
			tempo = tempo->next;
		draw_line(
			scale_xy((t_screen_xy){tempo->pos.x, tempo->pos.z}, editor->action.scalar, editor->action.offset),
			vec2(editor->mouse_data.x, editor->mouse_data.y), blue, &editor->buffer);
		editor->entity_list = ent;
	}
	if (editor->action.save_file)
		draw_input_string(editor->mapname, &editor->buffer, (editor->buffer.width * 0.5), map_saving);
	if (editor->action.open_file || editor->action.link_maps)
		update_editor_load_menu(&editor->buffer, &editor->action, editor->map_names);
}
