/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:35 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/16 12:33:05 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_color_from_action_data(int i, t_action *action, int end_sector)
{
	if ((i == button_plr_start && action->player_start_assigned)
		|| (i == button_assign_end_sector && end_sector >= 0))
		return (get_color(green));
	else if (i == button_plr_start || (i == button_assign_end_sector
			&& end_sector < 0))
		return (get_color(red));
	return (get_color(white));
}

static void	draw_button(t_editor *editor, t_button *button, int i)
{
	t_plx_modifier	mod;
	t_box			box;

	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	mod.len = ft_strlen((const char *)button->info.text);
	mod.colour = get_color_from_action_data(i,
			&editor->action, editor->end_sector);
	box.start = button->ltop;
	box.end = button->wh;
	draw_box(box, &editor->buffer, get_color(0xAAAAAA));
	ft_str_pxl(&editor->buffer, vec2(button->ltop.x + 8, button->ltop.y + 4),
		button->info.text, mod);
}

void	draw_buttons(t_editor *editor, t_texture **textures)
{
	int				i;
	t_box			box;

	box.start = vec2(0, 0);
	box.end = vec2(300, editor->buffer.height);
	draw_box(box, &editor->buffer, get_color(0x1f1f1f));
	i = 0;
	while (i < NBR_BUTTONS)
	{
		if (editor->button_list[i]->info.draw_depth
			== editor->action.draw_depth)
			draw_button(editor, editor->button_list[i], i);
		i++;
	}
	if (editor->action.draw_depth == entity)
		draw_entity_textfields(editor->temp_entity, &editor->buffer, textures);
	if (editor->action.draw_depth == sector)
		draw_sector_textfields(editor->temp_sector, &editor->buffer, textures);
	if (editor->action.draw_depth == wall)
		draw_wall_textfields(editor->temp_wall, &editor->buffer, textures);
}

static void	draw_map_list(t_buffer *buffer, t_action *action,
	char **map_names)
{
	int				y;
	int				i;
	t_plx_modifier	mod;
	t_box			box;

	box.start.x = 310;
	box.start.y = 100;
	box.end.x = 700;
	box.end.y = (100 + (15 * (action->end - action->start + 1)));
	draw_box(box, buffer, get_color(black));
	i = action->start;
	y = 0;
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

void	update_editor_load_menu(t_buffer *buffer, t_action *action,
	char **map_names)
{
	t_plx_modifier	mod;

	if (action->keysym == SDLK_DOWN)
		get_menu_range_key_down(&action->option, &action->start,
			&action->end, action->nbr_of_maps);
	else if (action->keysym == SDLK_UP)
		get_menu_range_key_up(&action->option, &action->start,
			&action->end, action->nbr_of_maps);
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
		ft_str_pxl(buffer, vec2(310, 70),
			"Select which map to load into editor", mod);
	}
	draw_map_list(buffer, action, map_names);
}
