/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:35 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/08 17:08:53 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_bbox_sector(t_sector_list *sector, t_buffer *buffer,
		t_action *action)
{
	float	point1;
	float	point2;
	float	point3;
	float	point4;
	Uint32	color;

	point1 = sector->bbox.start.x * action->scalar + action->offset.x;
	point2 = sector->bbox.start.y * action->scalar + action->offset.y;
	point3 = sector->bbox.end.x * action->scalar + action->offset.x;
	point4 = sector->bbox.end.y * action->scalar + action->offset.y;
	if (action->selected_sector == sector->idx_sector)
		color = get_color(lightgreen);
	else
		color = get_color(blue);
	draw_rect(vec2(point1, point2), vec2(ft_fabsf(point1 - point3),
		ft_fabsf(point2 - point4)), buffer, color);
}

void	draw_box(t_box box, t_buffer *buffer, Uint32 color)
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

void	draw_sector_textfields(t_sector_list *sector, t_buffer *buffer)
{
	t_plx_modifier	mod;

	if (!sector)
		return ;
	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	ft_c_pxl(buffer, vec2(165, 56), '0' + sector->idx_sector, mod);
	if (sector->sector_plot)
		ft_str_pxl(buffer, vec2(32, 580), (char *)sector->sector_plot, mod);
}

int	get_color_from_action_data(int i, t_action *action, int end_sector)
{
	if ((i == 7 && action->player_start_assigned) || (i == 4 && end_sector >= 0))
		return (get_color(green));
	else if (i == 7 || i == 4)
		return (get_color(red));
	return (get_color(white));
}

void	draw_buttons(t_button **blist, t_buffer *buffer,
		int draw_depth, t_action *action, int end_sector)
{
	int				i;
	t_box			box;
	t_plx_modifier	mod;

	box.start = vec2(0, 0);
	box.end = vec2(300, buffer->height);
	draw_box(box, buffer, get_color(0x282040));
	i = 0;
	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	mod.len = 0;
	while (i < NBR_BUTTONS)
	{
		if (blist[i]->info.draw_depth == draw_depth)
		{
			mod.len = ft_strlen((const char *)blist[i]->info.text);
			mod.colour = get_color_from_action_data(i, action, end_sector);
			box.start = blist[i]->ltop;
			box.end = blist[i]->wh;
			draw_box(box, buffer, get_color(0xAAAAAA));
			ft_str_pxl(buffer,
				vec2(blist[i]->ltop.x + 8, blist[i]->ltop.y + 4),
				blist[i]->info.text, mod);
		}
		i++;
	}
}

// void	draw_grid(t_buffer *buffer, t_action *action)
// {
// 	int		cells_on_sx;
// 	int		cells_on_sy;
// 	int		i;
// 	int		val;

// 	cells_on_sx = (buffer->width - 300) / action->scalar;
// 	cells_on_sy = (buffer->height) / action->scalar;
// 	i = 0;
// 	while (i <= cells_on_sy)
// 	{
// 		val = i * action->scalar + (action->offset.y % action->scalar);
// 		if (val < buffer->height)
// 			draw_line(vec2(300, val),
// 				vec2(buffer->width, val), get_color(0x808080), buffer);
// 		i++;
// 	}
// 	i = 0;
// 	while (i <= cells_on_sx)
// 	{
// 		val = (i * action->scalar + (action->offset.y % action->scalar)) + 300;
// 		if (val < buffer->width && val >= 300)
// 			draw_line(vec2(val, 0),
// 				vec2(val, buffer->height), get_color(0x808080), buffer);
// 		i++;
// 	}
// }

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
		test1 = world_to_screen((t_screen_xy){temp->pos.x, temp->pos.z}, editor->action.scalarf, editor->action.offsetf,
					&editor->buffer);
		test2 = world_to_screen((t_screen_xy){temp->pos.x + 1, temp->pos.z + 1}, editor->action.scalarf, editor->action.offsetf,
					&editor->buffer);
		temp_box.start = test1;
		temp_box.end = test2;
		if (temp->entity_idx == editor->action.selected_entity)
			color = get_color(white);
		else
			color = get_color(red);
		draw_box(temp_box, &editor->buffer, color);
		if (temp->is_linked)
		{
			while (link != NULL)
			{
				if (link->is_linked == temp->is_linked && link->is_linked > 1)
					draw_line(
						world_to_screen((t_screen_xy){temp->pos.x, temp->pos.z}, editor->action.scalarf, editor->action.offsetf,
							&editor->buffer),
						world_to_screen((t_screen_xy){link->pos.x, link->pos.z}, editor->action.scalarf, editor->action.offsetf,
							&editor->buffer),
						get_color(blue), &editor->buffer);
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
	char			*str;

	temp = *list;
	while (temp != NULL && temp->entity_idx != selected_entity)
		temp = temp->next;
	if (!temp)
		return ;
	mod.colour = white;
	mod.size = TEXT_SIZE;
	str = ft_itoa(temp->entity_idx);
	mod.len = ft_strlen(str);
	ft_strdel(&str);
	ft_c_pxl(buffer, vec2(100, 56), '0' + temp->entity_idx, mod);
	mod.len = 1;
	ft_c_pxl(buffer, vec2(100, 84), '0' + temp->entity_type, mod);
	ft_c_pxl(buffer, vec2(150, 114), '0' + temp->is_linked, mod);
	ft_c_pxl(buffer, vec2(165, 144), '0' + temp->is_revealed, mod);
	ft_c_pxl(buffer, vec2(165, 174), '0' + temp->is_static, mod);
	ft_c_pxl(buffer, vec2(100, 204), '0' + temp->state, mod);
}

// void	draw_input_string(unsigned char *string, t_buffer *buffer, int midpoint, int help_text)
// {
// 	t_plx_modifier	mod;

// 	mod.colour = white;
// 	mod.size = TEXT_SIZE;
// 	if (help_text == map_saving)
// 		str_pxl(buffer, vec2(midpoint - 100, 50), "Please input text string", mod);
// 	if (string != NULL)
// 		str_pxl(buffer, vec2(midpoint - 100, 70), (char *)string, mod);
// }

void	draw_input_string(unsigned char *string, t_buffer *buffer, int midpoint, int help_text)
{
	t_plx_modifier	mod;

	mod.colour = get_color(orange);
	mod.size = TEXT_SIZE;
	(void)help_text;
	if (help_text == map_saving)
	{
		mod.len = 25;
		ft_str_pxl(buffer, vec2(midpoint - 100, 50), "Please input text string", mod);
	}
	if (string != NULL)
	{
		mod.len = ft_strlen((const char *)string);
		ft_str_pxl(buffer, vec2(midpoint - 100, 70), (char *)string, mod);
	}
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
	mod.colour = get_color(orange);
	mod.size = TEXT_SIZE;
	if (action->link_maps)
		ft_str_pxl(buffer, vec2(310, 70), "Select which map to link to", mod);
	else
		ft_str_pxl(buffer, vec2(310, 70), "Select which map to load into editor", mod);
	box.start.x = 310;
	box.start.y = 100;
	box.end.x = 700;
	box.end.y = (100 + (15 * (action->end - action->start + 1)));
	draw_box(box, buffer, get_color(black));
	while (i <= action->end)
	{
		if (i == action->option)
			mod.colour = get_color(red);
		else
			mod.colour = get_color(white);
		ft_str_pxl(buffer, vec2(310, 100 + y),
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
		draw_grid(&editor->buffer, &editor->action);
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
			world_to_screen((t_screen_xy){tempo->pos.x, tempo->pos.z}, editor->action.scalarf, editor->action.offsetf,
				&editor->buffer),
			vec2(editor->mouse_data.x, editor->mouse_data.y), get_color(blue), &editor->buffer);
		editor->entity_list = ent;
	}
	if (editor->action.save_file)
		draw_input_string(editor->mapname, &editor->buffer, (editor->buffer.width * 0.5), map_saving);
	if (editor->action.open_file || editor->action.link_maps)
		update_editor_load_menu(&editor->buffer, &editor->action, editor->map_names);
}
