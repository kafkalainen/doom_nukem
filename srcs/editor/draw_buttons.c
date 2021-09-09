/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:35 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/09 19:38:21 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_sector_textfields(t_editor_sector *sector, t_buffer *buffer)
{
	t_plx_modifier	mod;
	char			*temp;

	if (!sector)
		return ;
	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	temp = ft_itoa(sector->idx_sector);
	mod.len = ft_strlen(temp) + 1;
	printf("idx len: %i\n", (int)mod.len);
	ft_str_pxl(buffer, vec2(165, 56), temp, mod);
	printf("%s\n", temp);
	ft_strdel(&temp);
	if (sector->sector_plot)
	{
		mod.len = ft_strlen((const char *)sector->sector_plot);
		ft_str_pxl(buffer, vec2(32, 580), (char *)sector->sector_plot, mod);
	}
		
}

int	get_color_from_action_data(int i, t_action *action, int end_sector)
{
	if ((i == 7 && action->player_start_assigned) || (i == 4 && end_sector >= 0))
		return (get_color(green));
	else if (i == 7 || i == 4)
		return (get_color(red));
	return (get_color(white));
}

void	draw_buttons(t_editor *editor, int end_sector, t_texture **textures)
{
	int				i;
	t_box			box;
	t_plx_modifier	mod;

	box.start = vec2(0, 0);
	box.end = vec2(300, editor->buffer.height);
	draw_box(box, &editor->buffer, get_color(0x1f1f1f));
	i = 0;
	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	mod.len = 0;
	while (i < NBR_BUTTONS)
	{
		if (editor->button_list[i]->info.draw_depth == editor->action.draw_depth)
		{
			mod.len = ft_strlen((const char *)editor->button_list[i]->info.text);
			mod.colour = get_color_from_action_data(i, &editor->action, end_sector);
			box.start = editor->button_list[i]->ltop;
			box.end = editor->button_list[i]->wh;
			draw_box(box, &editor->buffer, get_color(0xAAAAAA));
			ft_str_pxl(&editor->buffer,
				vec2(editor->button_list[i]->ltop.x + 8, editor->button_list[i]->ltop.y + 4),
				editor->button_list[i]->info.text, mod);
		}
		i++;
	}
	if (editor->action.draw_depth == entity)
		draw_entity_textfields(&editor->entity_list, editor->action.selected_entity, &editor->buffer, textures);
	if (editor->action.draw_depth == sector)
		draw_sector_textfields(editor->temp_sector, &editor->buffer);
}

void	draw_test_image(t_xy offset, t_texel *tex, t_buffer *buffer, t_xy scale) // bad name, possible duplicate, if the original can be modified for sprite maps
{
	t_screen_xy	current;

	current.x = 0;
	current.y = 0;
	scale.w = 1 / scale.w;
	while (current.y < scale.y)
	{
		current.x = 0;
		while (current.x < scale.x)
		{
			put_pixel(
				buffer,
				(t_pxl_coords){current.x + offset.x,
				current.y + offset.y},
				(Uint32)tex->texels[(tex->width * current.y
					* (int)scale.w) + current.x * (int)scale.w]);
			current.x++;
		}
		current.y++;
	}
}

void	draw_entity_textfields(t_entity_list **list, int selected_entity, t_buffer *buffer, t_texture **textures)
{
	t_entity_list	*temp;
	t_plx_modifier	mod;
	char			*str;
	t_box			box;
	t_texel			*tex;
	t_xy			scale;

	(void)textures;
	temp = *list;
	while (temp != NULL && temp->entity_idx != selected_entity)
		temp = temp->next;
	if (!temp)
		return ;
	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	str = ft_itoa(temp->entity_idx);
	mod.len = ft_strlen(str);
	ft_str_pxl(buffer, vec2(100, 56), str, mod);
	ft_strdel(&str);
	box.start = vec2(32, 230);
	box.end = vec2(132, 330);
	draw_box(box, buffer, get_color(black));
	tex = get_tex(editor_select_entity_tex(temp->entity_type), textures);
	if (temp->entity_type == skull_skulker || temp->entity_type == thing ||
		temp->entity_type == drone || temp->entity_type == crewmember)
	{
		scale.w = (float)(ft_fabsf(box.end.x - box.start.x) / 128);
		scale.x = 128;
		scale.y = 128;
		draw_test_image(box.start, tex, buffer, scale);
	}
	else
	{
		scale.w = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
		draw_image(box.start, tex, buffer, scale.w);
	}
	str = ft_itoa(temp->entity_type);
	mod.len = ft_strlen(str);
	ft_str_pxl(buffer, vec2(100, 84), str, mod);
	ft_strdel(&str);
	mod.len = 1;
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

void	draw_ui(t_editor *editor, t_texture **textures)
{
	t_editor_sector	*temp;
	t_entity_list	*ent;
	t_entity_list	*tempo;

	temp = editor->sector_list;
	if (editor->action.grid == 1)
		draw_grid(&editor->buffer, &editor->action);
	while (temp && temp->idx_sector != editor->action.selected_sector)
		temp = temp->next;
	draw_editor_sectors(editor);
	draw_editor_entities(editor, textures);
	ent = editor->entity_list;
	tempo = editor->entity_list;
	if (editor->action.link_entity == 1)
	{
		while (tempo->entity_idx != editor->action.selected_entity)
			tempo = tempo->next;
		draw_line(
			world_to_screen(vec2(tempo->pos.x, tempo->pos.z), editor->action.scalarf, editor->action.offsetf,
				&editor->buffer),
			vec2(editor->mouse_data.x, editor->mouse_data.y), get_color(blue), &editor->buffer);
		editor->entity_list = ent;
	}
	if (editor->action.save_file)
		draw_input_string(editor->mapname, &editor->buffer, (editor->buffer.width * 0.5), map_saving);
	if (editor->action.open_file || editor->action.link_maps)
		update_editor_load_menu(&editor->buffer, &editor->action, editor->map_names);
}
