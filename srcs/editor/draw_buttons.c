/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:35 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/15 15:24:17 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_sector_textfields(t_editor_sector *sector, t_buffer *buffer, t_texture **textures)
{
	t_plx_modifier	mod;
	char			*temp;
	t_box			box;
	float			scale;
	t_texel			*tex;

	if (!sector)
		return ;
	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	temp = ft_itoa(sector->idx_sector);
	mod.len = ft_strlen(temp) + 1;
	ft_str_pxl(buffer, vec2(165, 56), temp, mod);
	ft_strdel(&temp);
	box.start = vec2(32, 110);
	box.end = vec2(132, 210);
	tex = get_tex(sector->tex_floor, textures);
	scale = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
	draw_image(box.start, tex, buffer, scale);
	box.start = vec2(32, 240);
	box.end = vec2(132, 340);
	tex = get_tex(sector->tex_ceil, textures);
	scale = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
	draw_image(box.start, tex, buffer, scale);
	temp = ft_itoa(sector->light.intensity);
	mod.len = ft_strlen(temp) + 1;
	ft_str_pxl(buffer, vec2(250, 348), temp, mod);
	ft_strdel(&temp);
}

int	get_color_from_action_data(int i, t_action *action, int end_sector)
{
	if ((i == button_plr_start && action->player_start_assigned) || (i == button_assign_end_sector && end_sector >= 0))
		return (get_color(green));
	else if (i == button_plr_start || i == button_assign_end_sector)
		return (get_color(red));
	return (get_color(white));
}

static void	draw_wall_info(t_editor_walls *wall, t_buffer *buffer)
{
	t_plx_modifier	mod;
	char			*temp;

	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	temp = ft_itoa(wall->idx);
	mod.len = ft_strlen(temp);
	ft_str_pxl(buffer, vec2(165, 56), temp, mod);
	ft_strdel(&temp);
	temp = ft_itoa(wall->height.ceiling);
	mod.len = ft_strlen(temp);
	ft_str_pxl(buffer, vec2(255, 258), temp, mod);
	ft_strdel(&temp);
	temp = ft_itoa(wall->height.ground);
	mod.len = ft_strlen(temp);
	ft_str_pxl(buffer, vec2(255, 288), temp, mod);
	ft_strdel(&temp);
}

void	draw_wall_textfields(t_editor_walls *wall, t_buffer *buffer, t_texture **textures)
{
	t_box			box;
	float			scale;
	t_texel			*tex;

	if (!wall)
		return ;

	draw_wall_info(wall, buffer);
	if (wall->type < 0)
	{
		box.start = vec2(32, 110);
		box.end = vec2(132, 220);
		tex = get_tex(wall->type, textures);
		scale = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
		draw_image(box.start, tex, buffer, scale);
	}
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
		draw_entity_textfields(editor->temp_entity, &editor->buffer, textures);
	if (editor->action.draw_depth == sector)
		draw_sector_textfields(editor->temp_sector, &editor->buffer, textures);
	if (editor->action.draw_depth == wall)
		draw_wall_textfields(editor->temp_wall, &editor->buffer, textures);
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

void	draw_entity_textfields(t_entity_list *entity, t_buffer *buffer, t_texture **textures)
{
	t_plx_modifier	mod;
	char			*str;
	t_box			box;
	t_texel			*tex;
	t_xy			scale;

	if (!entity)
		return ;
	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	str = ft_itoa(entity->entity_idx);
	mod.len = ft_strlen(str) + 1;
	ft_str_pxl(buffer, vec2(165, 56), str, mod);
	ft_strdel(&str);
	str = ft_itoa(entity->entity_type);
	mod.len = ft_strlen(str) + 1;
	ft_str_pxl(buffer, vec2(165, 84), str, mod);
	ft_strdel(&str);
	box.start = vec2(32, 110);
	box.end = vec2(132, 220);
	draw_box(box, buffer, get_color(black));
	tex = get_tex(editor_select_entity_tex(entity->entity_type), textures);
	if (entity->entity_type == skull_skulker || entity->entity_type == thing ||
		entity->entity_type == drone || entity->entity_type == crewmember)
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
	mod.len = 1;
	ft_c_pxl(buffer, vec2(165, 229), '0' + entity->is_linked, mod);
	ft_c_pxl(buffer, vec2(165, 259), '0' + entity->is_revealed, mod);
	ft_c_pxl(buffer, vec2(165, 289), '0' + entity->is_static, mod);
	ft_c_pxl(buffer, vec2(165, 325), '0' + entity->state, mod);
}

void	draw_input_string(unsigned char *string, t_buffer *buffer, int midpoint, int help_text)
{
	t_plx_modifier	mod;
	int				y;
	int				i;
	int				lines;
	char			**arr;

	mod.colour = get_color(orange);
	mod.size = TEXT_SIZE;
	if (help_text == map_saving)
	{
		mod.len = 26;
		ft_str_pxl(buffer, vec2(midpoint - 100, 50), "Please input text string", mod);
		if (string != NULL)
		{
			mod.colour = get_color(white);
			mod.len = ft_strlen((const char *)string) + 1;
			ft_str_pxl(buffer, vec2(midpoint - 100, 70), (char *)string, mod);
		}
	}
	if (help_text == story_string)
	{
		mod.len = 86;
		ft_str_pxl(buffer, vec2(midpoint - 100, 50), "Please input sector story string, end writing with 'Return'. Add newline with 'Tab':", mod);
		if (string != NULL)
		{
			i = 0;
			y = 20;
			lines = get_nbr_of_lines(string);
			arr = ft_strsplit((const char *)string, '\n');
			if (arr)
			{
				mod.colour = get_color(white);
				while (i < lines && arr[i])
				{
					mod.len = ft_strlen(arr[i]);
					ft_str_pxl(buffer, vec2(midpoint - 100, 70 + (i * y)),arr[i], mod);
					i++;
				}
				free_array((unsigned char **)arr);
			}
		}
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
	{
		mod.len = 28;
		ft_str_pxl(buffer, vec2(310, 70), "Select which map to link to", mod);
	}
	else
	{
		mod.len = 37;
		ft_str_pxl(buffer, vec2(310, 70), "Select which map to load into editor", mod);
	}

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
		mod.len = ft_strlen(map_names[i]);
		ft_str_pxl(buffer, vec2(310, 100 + y),
			map_names[i], mod);
		y += 15;
		i++;
	}
}

void	draw_int_string_input(t_buffer *buffer, t_action *action,
		unsigned char **int_string)
{
	if (action->edit_ceiling_height)
		show_user_help("Input new ceiling height using number keys (-99 -- 99):",
			buffer, 0, get_color(orange));
	if (action->edit_floor_height)
		show_user_help("Input new floor height using number keys (-99 -- 99):",
			buffer, 0, get_color(orange));
	if (action->set_light_intensity)
		show_user_help("Set new light intensity using number keys (0-100):",
			buffer, 0, get_color(orange));
	if (action->set_all_sector_ceiling_heights)
		show_user_help("Set new ceiling height for all walls (-99 -- 99):",
			buffer, 0, get_color(orange));
	if (action->set_all_sector_floor_heights)
		show_user_help("Set new floor height for all walls (-99 -- 99):",
			buffer, 0, get_color(orange));
	if (action->edit_floor_height || action->edit_ceiling_height
		|| action->set_light_intensity || action->set_all_sector_ceiling_heights
		|| action->set_all_sector_floor_heights)
	{
		if (*int_string != NULL)
			show_user_help((char *)*int_string, buffer, 1, get_color(white));
	}
}

void	draw_help_text(t_action *action, t_buffer *buffer)
{
	if (action->convert_to_portal)
	{
		show_user_help("Use Mouse left click to select the sector",
			buffer, 0, get_color(orange));
		show_user_help("you want the portal to point to.",
			buffer, 1, get_color(orange));
		show_user_help("Use Mouse right click to cancel.",
			buffer, 2, get_color(orange));
	}
	if (action->delete)
	{
		show_user_help("Click entity or sector you wish to delete.",
			buffer, 0, get_color(orange));
	}
	if (action->create_sector == user_input)
	{
		show_user_help("Create at least three points to create a sector.",
			buffer, 0, get_color(orange));
		show_user_help("Sector has to be a convex polygon.",
			buffer, 1, get_color(orange));
		show_user_help("Last point must close sector.",
			buffer, 2, get_color(orange));
	}
	if (action->create_entity == allocate)
	{
		show_user_help("Click a point in a selected sector to create an entity.",
			buffer, 0, get_color(orange));
	}
}
